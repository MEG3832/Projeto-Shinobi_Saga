#include "Tengu.h"
#include "Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Tengu::Tengu(Jogador* pJ) :
			Inimigo(pJ),
			raio_perseg(250.0f)
		{
			paraEsq = true;
			nivel_maldade = 1;
			veloc = sf::Vector2f(0.01f, 0.01f); // Velocidade específica
			tempoAndar = 2.5f; // Tempo de "perambular" específico

			num_vidas = 200;

			cooldownAtordoado = 2.0f;

			//faz o corpo:

			corpo = new sf::RectangleShape(sf::Vector2f(140.0f, 150.0f));
			corpo->setPosition(sf::Vector2f(150, ALTURA_TELA - 50 - corpo->getSize().y));	// Posição qualquer para teste

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
								corpo->getPosition().y);


			//cuida da animação:

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Tengu::~Tengu()
		{

		}

		void Tengu::diminuiVida(int dano)
		{
			if (atordoado || estaMorto) {
				return;
			}

			Inimigo::diminuiVida(dano); // Chama a base para perder vida

			if (!estaMorto) {
				nivel_maldade++; // Aumenta o nível de maldade
				std::cout << "Tengu enfurecido! Nivel de maldade: " << nivel_maldade << std::endl;
			}

		}

		void Tengu::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				int dano_calculado = nivel_maldade * 50; // Dano = nivel_maldade * 50
				pJ->diminuiVida(dano_calculado);
				std::cout << "Tengu causou " << dano_calculado << " de dano! Vida do Jogador: " << pJ->getVida() << std::endl;
				empurrar(pJ); // Chama o empurrão (pode ser o base 'Inimigo::empurrar')
			}
			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}

		void Tengu::executar()
		{
			Inimigo::executar();

			// Só move se não estiver morto nem atordoado
			if (!estaMorto && !atordoado) {
				mover();
			}

			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);
		}

		void Tengu::perseguir(Jogador* pJ)
		{
			if (pJ) {

				float posJog_X = pJ->getPos().x + pJ->getTam().x / 2;
				float posInim_X = this->getPos().x + this->getTam().x / 2;


				float distanciaCentros = abs(posJog_X - posInim_X);
				float distanciaAtaque = abs((pJ->getTam().x / 2) + this->getTam().x / 2)-20.0f; //ajuste da distancia por testes

				if (distanciaCentros <= raio_perseg && distanciaCentros > distanciaAtaque)
				{
					if (posJog_X < posInim_X) //jogador está à esquerda do inimigo
					{
						paraEsq = true;
						animador->atualizarAnimInim(paraEsq, false, "Correndo");
						corpo->move(-veloc.x, 0.0f);

					}

					else if (posJog_X > posInim_X) //jogador está à direita do inimigo
					{
						paraEsq = false;
						animador->atualizarAnimInim(paraEsq, false, "Correndo");
						corpo->move(veloc.x, 0.0f);

					}


				}

				else if (distanciaCentros <= distanciaAtaque) //entrou na área de ataque!
				{
					if (relogioAtaque.getElapsedTime().asSeconds() >= cooldownAtaque)
					{
						animador->atualizarAnimInim(paraEsq, true, "Ataque3"); //se o cooldown está pronto, primeiro tocamos a animação!

						if (animador->getImgAtual("Ataque3") == 2) //se chegou no último frame, pode atacar!
						{
							atacar(pJ);
						}
					}
					else
					{
						animador->atualizarAnimInim(paraEsq, false, "Parado");
					}
				}

			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;
		}

		void Tengu::atacar(Jogador* pJ)
		{

			if (pJ)
			{
				float dt = relogioAtaque.getElapsedTime().asSeconds();

				if (dt >= cooldownAtaque)
				{
					relogioAtaque.restart();

					if (paraEsq)
					{
						float investida = -40.0f;
						corpo->move(investida, 0.0f);
					}

					else
					{
						float investida = 40.0f;
						corpo->move(investida, 0.0f);
					}

				}

			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;
		}


		void Tengu::inicializaAnimacoes()
		{
			if (animador) {


				//Animações em loop

				animador->addAnimacao("Imagens/Tengu/Idle.png", "Parado", 6, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Walk.png", "Andando", 8, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.0, 1.0));



				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Tengu/Attack_1.png", "Ataque1", 6, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Attack_2.png", "Ataque2", 4, 0.12f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Attack_3.png", "Ataque3", 3, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(1.0, 1.0));
			}

			else
				std::cout << "ponteiro de animacao nulo!" << std::endl;
		}


		void Tengu::mover()
		{
			if (jogAlvo) {

				//posição em x
				float posJog_X = jogAlvo->getPos().x + jogAlvo->getTam().x / 2;
				float posInim_X = this->getPos().x + this->getTam().x / 2;

				float distHorizontal = abs(posJog_X - posInim_X);

				//posição em y

				float posJog_Y = jogAlvo->getPos().y + jogAlvo->getTam().y / 2;
				float posInim_Y = this->getPos().y + this->getTam().y / 2;

				float distVertical = abs(posJog_Y - posInim_Y); // verificamos em y para evitar a perseguição sem sentido se o jogador estiver mto acima ou abaixo do inimigo

				float raio_vertical = this->getTam().y / 2; //esse seria o "raio_perseg" na vertical...

				if (distHorizontal <= raio_perseg && distVertical <= raio_vertical)
					perseguir(jogAlvo);

				else
					perambular();

			}

			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}
	}
}
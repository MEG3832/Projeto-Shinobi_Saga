#include "Kitsune.h"
#include "Projetil.h"

namespace Entidades
{
	namespace Personagens
	{
		Kitsune::Kitsune(Jogador* pJ) :
			Inimigo(pJ)
		{
			raio_ativacao = 250.0f;
			cooldownAtaque = 3.0f;
			nivel_maldade = 1; // nível de maldade base
			paraEsq = true;
			veloc = sf::Vector2f(0.03f, 0.05f);
			tempoAndar = 4.0f;

			num_vidas = 250;

			cooldownAtordoado = 1.0f;

			corpo = new sf::RectangleShape(sf::Vector2f(140.0f, 150.0f));
			//corpo->setPosition(pos); //posicao??

			corpo->setPosition(300.0f, ALTURA_TELA - 100 - corpo->getSize().y);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 75, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Kitsune::~Kitsune()
		{
			pProjetil = nullptr;
		}


		void Kitsune::executar()
		{
			Inimigo::executar(); //verificar se basta isso...
		}


		void Kitsune::mover()
		{
			if (jogAlvo)
			{
				//posição em x
				float posJog_X = jogAlvo->getPos().x + jogAlvo->getTam().x / 2;
				float posInim_X = this->getPos().x + this->getTam().x / 2;

				float distHorizontal = abs(posJog_X - posInim_X);

				//posição em y

				float posJog_Y = jogAlvo->getPos().y + jogAlvo->getTam().y / 2;
				float posInim_Y = this->getPos().y + this->getTam().y / 2;

				float distVertical = abs(posJog_Y - posInim_Y);

				float raio_vertical = this->getTam().y / 2;

				if (distHorizontal <= raio_ativacao && distVertical <= raio_vertical)
				{
					//verifica em que lado o jogador está...

					if (posJog_X < posInim_X) //jogador está à esquerda do inimigo
					{
						paraEsq = true;

					}

					else //jogador está à direita do inimigo
					{
						paraEsq = false;

					}

					if (pProjetil && relogioAtaque.getElapsedTime().asSeconds() >= cooldownAtaque && !pProjetil->getEstadoProj())
					{
						animador->atualizarAnimInim(paraEsq, true, "Ataque3"); //se o cooldown está pronto, primeiro tocamos a animação!

						if (animador->getImgAtual("Ataque3") == 6) //se chegou no último frame, pode atacar!
						{
							atiraProjetil();
						}
					}
					else
					{
						animador->atualizarAnimInim(paraEsq, false, "Parado");
					}

				}

				else
					perambular();
			}

			else
				std::cout << "ponteiro do jogador eh nulo!" << std::endl;
		}

		void Kitsune::atiraProjetil()
		{
			relogioAtaque.restart();

			pProjetil->setEstadoProj(true); //apenas setamos o estado do projétil, já que o que será feito (dependendo do estado dele), será tratado no executar do projétil.

			if (paraEsq) {
				pProjetil->getCorpo()->setPosition(this->getPos().x, this->getPos().y + 75.0f); //centralizo o projétil bem na frente da kitsune
				pProjetil->setVelocidade(sf::Vector2f(-0.05f, 0.0f));
			}
			else {

				pProjetil->getCorpo()->setPosition(this->getPos().x, this->getPos().y + 75.0f);
				pProjetil->setVelocidade(sf::Vector2f(0.05f, 0.0f));
			}

		}

		void Kitsune::salvar()
		{
			return;
		}

		void Kitsune::setProjetil(Projetil* pProj)
		{
			if (pProj)
				pProjetil = pProj;
			else
				std::cout << "ponteiro do projetil eh nulo!" << std::endl;
		}

		void Kitsune::inicializaAnimacoes()
		{
			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Kitsune/Idle.png", "Parado", 8, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Walk.png", "Andando", 8, 0.20f, sf::Vector2f(1.0, 1.0));


				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Kitsune/Attack_3.png", "Ataque3", 7, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Dead.png", "Derrotado", 10, 0.45f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Hurt.png", "Ferido", 2, 0.17f, sf::Vector2f(1.0, 1.0));

			}
			else
				std::cout << "ponteiro de animacao nulo!" << std::endl;
		}

		void Kitsune::danificar(Jogador* pJ)
		{
			return;
		}

	}
}
#include "Tengu.h"
#include "Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Tengu::Tengu(Jogador* pJ) :
			Inimigo(pJ),
			paraEsq(true)
		{
			nivel_maldade = 1;

			//faz o corpo:

			corpo = new sf::RectangleShape(sf::Vector2f(100.0f, 160.0f));
			corpo->setPosition(sf::Vector2f(100, 400));	// Posição qualquer para teste


			//cuida da animação:

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Tengu::~Tengu()
		{
			jogAlvo = nullptr;

		}

		void Tengu::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				pJ->diminuiVida(nivel_maldade);
				std::cout << pJ->getVida() << std::endl;
				empurrar(pJ);
			}

			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}

		void Tengu::executar()
		{
			mover();
		}

		void Tengu::perseguir(Jogador* pJ)
		{
			if (pJ) {

				float posJog_X = pJ->getPos().x + pJ->getTam().x / 2;
				float posInim_X = this->getPos().x + this->getTam().x / 2;
				      

				float distanciaCentros = abs(posJog_X - posInim_X);
				float distanciaAtaque = abs((pJ->getTam().x / 2) + this->getTam().x/2) +30.0f; //30pixels para a distancia entre as bordas dos personagens

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

					if(paraEsq) 
					{
						float investida = - 40.0f;
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

				animador->addAnimacao("Imagens/Tengu/Idle.png", "Parado", 6, 0.20f, sf::Vector2f(1.5, 1.0));
				animador->addAnimacao("Imagens/Tengu/Walk.png", "Andando", 8, 0.20f, sf::Vector2f(1.5, 1.0));
				animador->addAnimacao("Imagens/Tengu/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.5, 1.0));



				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Tengu/Attack_1.png", "Ataque1", 6, 0.1f, sf::Vector2f(1.5, 1.0));
				animador->addAnimacao("Imagens/Tengu/Attack_2.png", "Ataque2", 4, 0.12f, sf::Vector2f(1.5, 1.0));
				animador->addAnimacao("Imagens/Tengu/Attack_3.png", "Ataque3", 3, 0.1f, sf::Vector2f(1.5, 1.0));
				animador->addAnimacao("Imagens/Tengu/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(1.5, 1.0));
				animador->addAnimacao("Imagens/Tengu/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(1.5, 1.0));
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

				else {

					if (relogioAndar.getElapsedTime().asSeconds() >= tempoAndar) //se passou o tempo para parar de andar 
					{															 // ou se passou o tempo para começar a andar
						relogioAndar.restart();

						andando = !andando;

						//sorteio para qual lado ele vai!
						if (rand() % 2 == 0)
						{
							paraEsq = true;
						}
						else
						{
							paraEsq = false;
						}


					}

					if (andando)
					{
						if (paraEsq)
							corpo->move(-veloc.x, 0.0f);
						else
							corpo->move(veloc.x, 0.0f);

						animador->atualizarAnimInim(paraEsq, false, "Andando");

					}

					else //está parado
					{
						corpo->move(0.0f, 0.0f);
						animador->atualizarAnimInim(paraEsq, false, "Parado");
					}

				}

			}

			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}
	}
}
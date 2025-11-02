#include "Tengu.h"
#include "Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Tengu::Tengu(Jogador* pJ) :
			Inimigo(pJ),
			cooldownAtaque(3.0f),
			relogioAtaque(),
			paraEsq(true)
		{
			nivel_maldade = 1;

			//faz o corpo:

			corpo = new sf::RectangleShape(sf::Vector2f(100.0f, 160.0f));
			corpo->setPosition(sf::Vector2f(400, 400));	// Posição qualquer para teste


			//cuida da animação:

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Tengu::~Tengu()
		{
			//..
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
			if (jogAlvo)
			{
				perseguir(jogAlvo);
			}

			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
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
					animador->atualizarAnimInim(paraEsq, true, "Ataque3");
					atacar(pJ);
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
						animador->atualizarAnimInim(paraEsq, false, "Ataque3");
						float investida = - 40.0f;
						corpo->move(investida, 0.0f);
					}

					else 
					{
						animador->atualizarAnimInim(paraEsq, false, "Ataque3");
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

			//Animações em loop

			animador->addAnimacao("Imagens/Tengu/Idle.png", "Parado", 6, 0.20f, sf::Vector2f(1.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.5, 1.0));

			

			//Animações que só devem rodar uma vez

			animador->addAnimacao("Imagens/Tengu/Attack_1.png", "Ataque1", 6, 0.1f, sf::Vector2f(1.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Attack_2.png", "Ataque2", 4, 0.12f, sf::Vector2f(1.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Attack_3.png", "Ataque3", 3, 0.1f, sf::Vector2f(1.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(1.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(1.5, 1.0));

		}
	}
}
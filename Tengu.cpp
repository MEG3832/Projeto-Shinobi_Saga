#include "Tengu.h"
#include "Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Tengu::Tengu(Jogador* pJ) :
			Inimigo(pJ),
			//atacando(false),
			cooldownAtaque(2.5f),
			relogioAtaque(),
			paraEsq(true)
		{
			nivel_maldade = 1;

			//faz a espada

			//espada = new sf::RectangleShape(sf::Vector2f(5.0f, 5.0f));
			//espada->setFillColor(sf::Color::Red);

			//faz o corpo:

			corpo = new sf::RectangleShape(sf::Vector2f(100.0f, 160.0f));
			corpo->setPosition(sf::Vector2f(400, 300));	// Posição qualquer para teste
			//corpo->setFillColor(sf::Color::Red);	// Pintando de vermelho só pra ficar visivel

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

				/*float tempoDecorrido = relogioAtaque.getElapsedTime().asSeconds();

				if (atacando)
				{
					// verificando a colisão da espada manualmente aqui...
					if (espada->getGlobalBounds().intersects(jogAlvo->getCorpo()->getGlobalBounds()))
					{
						jogAlvo->diminuiVida(2*nivel_maldade);
						empurrar(jogAlvo);
						atacando = false;
						espada->setFillColor(sf::Color::Transparent); // Esconde a espada
						relogioAtaque.restart(); // inicia o cooldown
					}

					if (tempoDecorrido > 0.5f) // ataque dura 0.5 segundos
					{
						atacando = false;
						espada->setFillColor(sf::Color::Transparent); // Esconde a espada
						relogioAtaque.restart(); // inicia o cooldown
					}
				}
				
				else // se não estiver atacando, vai perseguir e decidir se vai atacar
				{
					// move o corpo E decide se deve atacar
					perseguir(jogAlvo);
				}

				// Atualize a posição da espada para seguir o corpo
				atualizarPosEspada();*/
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
				float distanciaAtaque = abs((pJ->getTam().x / 2) + this->getTam().x/2)+20.0f; //20pixels para a distancia entre as bordas dos personagens

				if (distanciaCentros <= raio_perseg && distanciaCentros > distanciaAtaque) 
				{
					if (posJog_X < posInim_X) //jogador está à esquerda do inimigo
					{
						paraEsq = true;
						animador->atualizarAnimInim(paraEsq, false, "Correndo");
						corpo->move(-veloc.x, 0.0f);
						
					}

					else if (posJog_X > posInim_X)
					{
						paraEsq = false;
						animador->atualizarAnimInim(paraEsq, false, "Correndo");
						corpo->move(veloc.x, 0.0f);
						
					}
					
						
				}

				else if (distanciaCentros <= distanciaAtaque) //entrou na área de ataque!
				{
					animador->atualizarAnimInim(paraEsq, false, "Parado");
					atacar(pJ);
				}

				//50% de chance de só continuar andando e dar dano por empurrão (1 de dano)
				//50% de chance de atacar -> rectangle shape aparece na borda do inimigo e temos que tratar colisao da espada com o jogador... (2 de dano)

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

					if (rand() % 2 == 0) // 50% de chance de dar uma investida e dar dano por empurrão (1 de dano)
					{
						if(paraEsq) 
						{
							animador->atualizarAnimInim(paraEsq, false, "Correndo");
							float investida = - (veloc.x + 0.2f);
							corpo->move(investida, 0.0f);
						}

						else
						{
							animador->atualizarAnimInim(paraEsq, false, "Correndo");
							float investida = (veloc.x + 0.2f);
							corpo->move(investida, 0.0f);
						}
					}

					else
					{
						animador->atualizarAnimInim(paraEsq, false, "Ataque1");
						pJ->diminuiVida(2 * nivel_maldade);
						empurrarForte(pJ);

					}
				}
			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;
		}

		void Tengu::empurrarForte(Jogador* pJ)
		{
			float força_empurrao_forte = 2.0f; // (O Inimigo usa 1.5f)

			if (pJ) {
				sf::Vector2f centroJog = pJ->getPos() + (pJ->getTam()) / 2.0f;
				sf::Vector2f centroInim = this->getPos() + (this->getTam()) / 2.0f;
				sf::Vector2f vetor = centroJog - centroInim;
				float modulo = std::sqrt(vetor.x * vetor.x + vetor.y * vetor.y);

				if (modulo != 0)
					vetor = vetor / modulo;

				vetor *= força_empurrao_forte; // Aplica a força FORTE
				pJ->setVelKnockBack(vetor);
			}
			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;
		}

		/*void Tengu::atualizarPosEspada()
		{
			float posX;
			if (paraEsq)
			{
				posX = corpo->getPosition().x - espada->getSize().x; // à esquerda
			}
			else
			{
				posX = corpo->getPosition().x + corpo->getSize().x; // à direita
			}

			float posY = corpo->getPosition().y + (corpo->getSize().y / 2); // no meio
			espada->setPosition(posX, posY);
		}*/

		//void Tengu::empurrar(Jogador* pJ)
		//{

		//}

		//void Tengu::mover()
		//{
			//return;
		//}

		void Tengu::inicializaAnimacoes()
		{
			//Animações em loop

			animador->addAnimacao("Imagens/Tengu/Idle.png", "Parado", 6, 0.20f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Walk.png", "Andando", 8, 0.12f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(2.5, 1.0));

			

			//Animações que só devem rodar uma vez

			animador->addAnimacao("Imagens/Tengu/Attack_1.png", "Ataque1", 6, 0.16f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Attack_2.png", "Ataque2", 4, 0.12f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Attack_3.png", "Ataque3", 3, 0.18f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(2.5, 1.0));

		}
	}
}
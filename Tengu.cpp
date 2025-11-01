#include "Tengu.h"

namespace Entidades
{
	namespace Personagens
	{
		Tengu::Tengu(Jogador* pJ) :
			Inimigo(pJ)
		{
			espada = new sf::RectangleShape(sf::Vector2f(30.0f, 5.0f));

			corpo = new sf::RectangleShape(sf::Vector2f(90.0f, 140.0f));
			corpo->setPosition(sf::Vector2f(400, 300));	// Posição qualquer para teste
			corpo->setFillColor(sf::Color::Red);	// Pintando de vermelho só pra ficar visivel

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Tengu::~Tengu()
		{
			//..
		}

		void Tengu::perseguir(Jogador* pJ)
		{
			if (pJ) {

				float posJog_X = pJ->getPos().x + pJ->getTam().x / 2;
				float posInim_X = this->getPos().x + this->getTam().x / 2;

				float distanciaCentros = abs(posJog_X - posInim_X);
				float distancia_aux = abs((pJ->getTam().x / 2) + espada->getSize().x + this->getPos().x);

				if (distancia <= raio_perseg && distancia >= distancia_aux && posJog_X < posInim_X) //jogador está à esquerda do inimigo
				{
					corpo->move(-veloc.x, 0.0f);
				}

				else if (distancia <= raio_perseg && distancia >= distancia_aux && posJog_X > posInim_X)
				{
					corpo->move(veloc.x, 0.0f);
				}

				//50% de chance de só continuar andando e dar dano por empurrão (1 de dano)
				//50% de chance de atacar -> rectangle shape aparece na borda do inimigo e temos que tratar colisao da espada com o jogador... (2 de dano)

			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;
		}


		void Tengu::inicializaAnimacoes()
		{
			//Animações em loop

			animador->addAnimacao("Imagens/Tengu/Idle.png", "Parado", 6, 0.20f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Tengu/Walk.png", "Andando", 8, 0.12f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Tengu/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(6.0, 2.0));

			

			//Animações que só devem rodar uma vez

			animador->addAnimacao("Imagens/Tengu/Attack_1.png", "Ataque1", 6, 0.16f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Tengu/Attack_2.png", "Ataque2", 4, 0.12f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Tengu/Attack_3.png", "Ataque3", 3, 0.18f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Tengu/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Tengu/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(6.0, 2.0));

		}
	}
}
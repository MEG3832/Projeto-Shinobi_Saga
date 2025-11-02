#include "Inimigo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Personagens {

		Inimigo::Inimigo(Jogador* pJ) :
			Personagem(),
			nivel_maldade(1),
			raio_perseg(300.0f),
			veloc(0.05f,0.05f),
			jogAlvo(pJ)
		{
			corpo = new sf::RectangleShape(sf::Vector2f(30.0f, 30.0f));
			corpo->setPosition(sf::Vector2f(400, 300));	// Posição qualquer para teste
			corpo->setFillColor(sf::Color::Red);	// Pintando de vermelho só pra ficar visivel
			
		}

		Inimigo::~Inimigo() {
			nivel_maldade = -1;
		}

		void Inimigo::salvarDataBuffer() {
			return;
		}

		void Inimigo::executar() {

			perseguir(jogAlvo);
			
		}

		void Inimigo::danificar(Jogador* pJ) { //quando criar inimigos fácil, médio e chefao, será virtual

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

		void Inimigo::empurrar(Jogador* pJ)
		{
			//nesse método, vamos calcular a direção do vetor KnockBack que queremos passar para o jogador,
			// e, depois disso, iremos multiplicar por uma "força" (intensidade)

			sf::Vector2f velKnockBack;
			float força_empurrao = 1.5f;

			if (pJ) {

				//calcula os centros do inimigo e do jogador

				sf::Vector2f centroJog = pJ->getPos() + (pJ->getTam()) / 2.0f;
				sf::Vector2f centroInim = this->getPos() + (this->getTam()) / 2.0f;

				sf::Vector2f vetor = centroJog - centroInim; //nessa ordem!

				//normalizamos o vetor... e para isso, calculamos seu módulo

				float modulo = std::sqrt(vetor.x * vetor.x + vetor.y * vetor.y);

				if(modulo!=0)
					vetor = vetor / modulo; //agora o vetor é um vetor normalizado!

				vetor *= força_empurrao;

				pJ->setVelKnockBack(vetor);

			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;

		}

		void Inimigo::perseguir(Jogador* pJ)
		{
			if (pJ) {

				float posJog_X = pJ->getPos().x + pJ->getTam().x / 2;
				float posInim_X = this->getPos().x + this->getTam().x / 2;

				float distancia = abs(posJog_X - posInim_X);
				
				if (distancia <= raio_perseg && posJog_X<posInim_X) //jogador está à esquerda do inimigo
				{
					corpo->move(-veloc.x, 0.0f);
				}

				else if (distancia <= raio_perseg && posJog_X > posInim_X)
				{
					corpo->move(veloc.x, 0.0f);
				}
			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;

		}

		void Inimigo::salvar() {
			return;
		}

		void Inimigo::mover() {
			return;
		}

		void Inimigo::inicializaAnimacoes() {
			return;
		}

	}

}
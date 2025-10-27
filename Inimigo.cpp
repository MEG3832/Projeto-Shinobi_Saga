#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		Inimigo::Inimigo() :
			Personagem(),
			nivel_maldade(0)
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
			return;
		}

		void Inimigo::danificar(Jogador* pJ) {
			return;
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
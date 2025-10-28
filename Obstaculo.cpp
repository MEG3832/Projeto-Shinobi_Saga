#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		Obstaculo::Obstaculo() :
			Entidade(),
			danoso(false)
		{
			corpo = new sf::RectangleShape(sf::Vector2f(50.0f, 30.0f));
			corpo->setPosition(sf::Vector2f(450, 500));	// Posição qualquer para teste
			corpo->setFillColor(sf::Color::Blue);	// Pintando de vermelho só pra ficar visivel
		}

		Obstaculo::~Obstaculo() {

		}

		void Obstaculo::salvarDataBuffer() {
			return;
		}

		void Obstaculo::executar() {
			return;
		}

		void Obstaculo::salvar() {
			return;
		}

		void Obstaculo::obstaculizar(Personagens::Jogador* pJ) {
			return;
		}

		void Obstaculo::inicializaAnimacoes() {
			return;
		}

	}

}
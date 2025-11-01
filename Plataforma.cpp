#include "Plataforma.h"

namespace Entidades {

	namespace Obstaculos {

		Plataforma::Plataforma() :
			Obstaculo(),
			altura(55),
			comprimento(180),
			textura(pGG->carregarTextura("Imagens/Obstaculos/Plataforma.png"))
		{
			danoso = false;

			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			corpo->setPosition(200.0f, 300.0f);
			corpo->setTexture(&textura);
		}

		Plataforma::~Plataforma() {
			altura = -1;
			comprimento = -1;
		}

		void Plataforma::executar() {
			return;
		}

		void Plataforma::obstaculizar(Personagens::Jogador* p) {
			return;
		}

		void Plataforma::salvar() {
			return;
		}

	}

}
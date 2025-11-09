#include "Plataforma.h"

namespace Entidades {

	namespace Obstaculos {

		Plataforma::Plataforma() :
			Obstaculo(),
			altura(55),
			comprimento(120),
			//comprimento(180),
			//textura(pGG->carregarTextura("Imagens/Obstaculos/Plataforma_DarkForest.png")),
			textura(pGG->carregarTextura("Imagens/Obstaculos/Plataforma_Village.png"))
		{
			danoso = false;

			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			corpo->setPosition(200.0f, 400.0f);
			corpo->setTexture(&textura);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize()));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);
		}

		Plataforma::~Plataforma() {
			altura = -1;
			comprimento = -1;
		}

		void Plataforma::executar() {
			sofrerGravidade();

			sofrerContraForca();

			corpo->move(veloc.x, veloc.y);
			hitBox->move(veloc.x, veloc.y);
		}

		void Plataforma::obstaculizar(Personagens::Jogador* p) {
			if (p) {
				if (corpo->getPosition().y == p->getCorpo()->getPosition().y + p->getCorpo()->getSize().y) {
					p->setNoChao();
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel obstaculizar pois o jogador eh NULL" << std::endl;
			}
		}

		void Plataforma::salvar() {
			return;
		}

		void Plataforma::sofrerContraForca() {
			float aceleracao = -GRAVIDADE;
			veloc.y += aceleracao;
		}

	}

}
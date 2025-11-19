#include "Plataforma.h"

namespace Entidades {

	namespace Obstaculos {

		Plataforma::Plataforma() :
			Obstaculo(),
			altura(55),
			comprimento(180),
			//textura(pGG->carregarTextura("Imagens/Obstaculos/Plataforma_DarkForest.png")),
			textura(pGG->carregarTextura("Imagens/Obstaculos/Plataforma_Village.png"))
		{
			danoso = false;

			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			corpo->setTexture(&textura);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize()));
		}

		Plataforma::~Plataforma() {
			altura = -1;
			comprimento = -1;
		}

		void Plataforma::executar() {
			sofrerContraForca();
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

		void Plataforma::salvar() {	// Estou querendo tirar essa função pois salvarDataBuffer eh equivalente no que eu quero fazer
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);
		
			buffer_plataformas.push_back(buffer);
		}

		void Plataforma::salvarDataBuffer(nlohmann::json& buffer) {
			Obstaculo::salvarDataBuffer(buffer);

			// Nao ha nada especifico da plataforma pra salvar. Da ate pra tirar esse altura e comprimento, ja que o corpo tem size
		}

	}

}
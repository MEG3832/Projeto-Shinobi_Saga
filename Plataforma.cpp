#include "Plataforma.h"

namespace Entidades {

	namespace Obstaculos {

		Plataforma::Plataforma(int id) :
			Obstaculo(),
			altura(55),	
			comprimento(180),
			textura(),
			cura(25)
		{
			if (pGG) {
				if (1 == id) {
					textura = pGG->carregarTextura("Imagens/Obstaculos/Plataforma_Village.png");
				}
				else if (2 == id) {
					textura = pGG->carregarTextura("Imagens/Obstaculos/Plataforma_DarkForest.png");
				}
			}

			danoso = false;

			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			if (corpo) {
				corpo->setTexture(&textura);
			}

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize()));
		}

		Plataforma::~Plataforma() {
			altura = -1;
			comprimento = -1;
			cura = 0;
		}

		void Plataforma::executar() {
			sofrerContraForca();
		}

		void Plataforma::obstaculizar(Personagens::Jogador* p) {
			if (p) {

				if (corpo->getPosition().y == p->getCorpo()->getPosition().y + p->getCorpo()->getSize().y) {
					p->setNoChao();
				}
				p->curar(cura);
				cura = 0;
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

				buffer["cura"] = cura;
		}

		void Plataforma::carregar(const nlohmann::json& j) {
			
			try {
				cura = j.at("cura").get<int>();
			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Alguma das chaves estah ausente." << e.what() << std::endl;
			}

			Obstaculo::carregar(j);
		}

	}

}
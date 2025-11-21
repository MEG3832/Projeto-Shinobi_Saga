#include "Armadilha_de_urso.h"

namespace Entidades {

	namespace Obstaculos {

		Armadilha_de_urso::Armadilha_de_urso() :
			Obstaculo(),
			lado(60.0),
			danosidade(2),	// Estou imaginando que cada vida tem uns 100
			cooldown_atordoamento(3.0f),
			timer(),
			dt(0.0f)
		{
			intransponivel = false;
			danoso = true;
			corpo = new sf::RectangleShape(sf::Vector2f(lado, lado));

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 30.0f, corpo->getSize().y));

			inicializaAnimacoes();
		}

		Armadilha_de_urso::~Armadilha_de_urso() {
			lado = -1.0;
			danosidade = -1;
			danoso = false;
			cooldown_atordoamento = 0.0;
			timer.restart();
			dt = 0.0;
		}

		void Armadilha_de_urso::executar() {

			if (!danoso) {
				atualizaAnimacao();
			}

			sofrerContraForca();
		}

		void Armadilha_de_urso::obstaculizar(Personagens::Jogador* pJ) {
			if (dt < cooldown_atordoamento) {
				if (danoso) {
					if (pJ) {
						pJ->setAtordoado(true);
						pJ->diminuiVida(danosidade);
					}
					else {
						std::cerr << "ERRO: nao eh possivel atordoar pois o jogador eh NULL" << std::endl;
					}

					danoso = false;
					dt = 0.0;
					timer.restart();
				}
				else {
					dt += timer.getElapsedTime().asSeconds();
					timer.restart();
				}
			}
			else {
				if (pJ) {
					pJ->setAtordoado(false);
				}
				else {
					std::cerr << "ERRO: nao eh possivel atordoar pois o jogador eh NULL" << std::endl;
				}
			}
		}

		void Armadilha_de_urso::salvar() {
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_armadilhas.push_back(buffer);
		}

		void Armadilha_de_urso::salvarDataBuffer(nlohmann::json& buffer) {

			Obstaculo::salvarDataBuffer(buffer);

			buffer["dt"] = dt;
		}

		void Armadilha_de_urso::carregar(const nlohmann::json& j) {
			
			dt = j.at("dt").get<float>();

			Obstaculo::carregar(j);
		}

		void Armadilha_de_urso::inicializaAnimacoes() {
			if (corpo) {
				setAnimador(corpo);
				animador->addAnimacao("Imagens/Obstaculos/Armadilha_de_urso.png", "ataque", 4, 0.2, sf::Vector2f(1.0, 1.0));
			}
			else {
				std::cerr << "Nao eh possivel inicializar a animacao pois o corpo eh NULL" << std::endl;
			}

			atualizaAnimacao();
		}

		void Armadilha_de_urso::atualizaAnimacao() {
				if (animador) {
					animador->atualizarAnimJog(false, false, false, true, "ataque");
				}
				else {
					std::cerr << "Nao eh possivel atualizar a animacao pois o animador eh NULL" << std::endl;
				}
		}

	}

}

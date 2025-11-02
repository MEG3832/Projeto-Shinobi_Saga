#include "Armadilha_de_urso.h"

namespace Entidades {

	namespace Obstaculos {

		Armadilha_de_urso::Armadilha_de_urso() :
			Obstaculo(),
			altura(30),
			comprimento(30),
			danosidade(2),	// Estou imaginando que cada vida tem uns 100
			cooldown(3.0f),
			timer(),
			dt(0.0f)
		{
			intransponivel = false;
			danoso = true;
			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			if (corpo) {
				corpo->setPosition(400.0, ALTURA_TELA - 60 - altura);
				inicializaAnimacoes();
			}
			else {
				std::cerr << "Nao eh possivel inicializar a animacao pois o corpo eh NULL" << std::endl;
			}
		}

		Armadilha_de_urso::~Armadilha_de_urso() {
			altura = -1;
			comprimento = -1;
			danosidade = -1;
			danoso = false;
		}

		void Armadilha_de_urso::executar() {
			return;
		}

		void Armadilha_de_urso::obstaculizar(Personagens::Jogador* pJ) {
			if (dt < cooldown) {
				if (danoso) {
					if (pJ) {
						pJ->setAtordoado(true);
						pJ->diminuiVida(danosidade);
					}
					else {
						std::cerr << "ERRO: nao eh possivel atordoar pois o jogador eh NULL" << std::endl;
					}

					danoso = false;
					timer.restart();
				}
				else {
					dt = timer.getElapsedTime().asSeconds();
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
			atualizaAnimacao();
		}

		void Armadilha_de_urso::salvar() {
			return;
		}

		void Armadilha_de_urso::inicializaAnimacoes() {
			if (corpo) {
				setAnimador(corpo);
				animador->addAnimacao("Imagens/Obstaculos/Armadilha_de_urso.png", "ataque", 4, 0.2, sf::Vector2f(2.0, 2.0));
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

		void salvarDataBuffer() {
			return;
		}

	}

}

#include "Armadilha_de_urso.h"

namespace Entidades {

	namespace Obstaculos {

		Armadilha_de_urso::Armadilha_de_urso() :
			Obstaculo(),
			altura(60),
			comprimento(60),
			danosidade(2),	// Estou imaginando que cada vida tem uns 100
			cooldown(3.0f),
			timer(),
			dt(0.0f)
		{
			intransponivel = false;
			danoso = true;
			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			corpo->setPosition(400.0, ALTURA_TELA - 30 - altura);	// 35 é a altura desde a borda inferior da janela

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 30.0f, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
								corpo->getPosition().y);

			inicializaAnimacoes();
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

		void salvarDataBuffer() {
			return;
		}

	}

}

#include "Redemoinho.h"

namespace Entidades {
	
	namespace Obstaculos {

		Redemoinho::Redemoinho() :
			Obstaculo(),
			altura(60),
			comprimento(60),
			dano(1),
			dano_unico (false)
		{
			intransponivel = false;
			danoso = true;
			corpo = new sf::RectangleShape(sf::Vector2f(comprimento, altura));
			if (corpo) {
				corpo->setPosition(100.0, ALTURA_TELA - 160 - altura);
				inicializaAnimacoes();
			}
			else {
				std::cerr << "Nao eh possivel inicializar a animacao pois o corpo eh NULL" << std::endl;
			}
		}

		Redemoinho::~Redemoinho() {
			altura = -1;
			comprimento = -1;
			dano = -1;
		}

		void Redemoinho::executar() {
			atualizaAnimacao();
			if (animador->getImgAtual("ataque") < 4 || animador->getImgAtual("ataque") > 11) {
				dano_unico = true;
				danoso = false;
			}
			else {
				danoso = true;
			}

		}

		void Redemoinho::obstaculizar(Personagens::Jogador* pJ) {
			if (pJ) {
				if (dano_unico && danoso) {
					pJ->diminuiVida(dano);
					dano_unico = false;
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel diminuir a vida pois o jogador eh NULL" << std::endl;
			}
		}

		void Redemoinho::salvar() {
			return;
		}

		void Redemoinho::inicializaAnimacoes() {
			if(corpo) {
				setAnimador(corpo);
				animador->addAnimacao("Imagens/Obstaculos/redemoinho.png", "ataque", 13, 0.13, sf::Vector2f(2.0, 2.0));
			}
			else {
				std::cerr << "Nao eh possivel inicializar a animacao pois o corpo eh NULL" << std::endl;
			}
		}

		void Redemoinho::atualizaAnimacao() {
			if(animador) {
				animador->atualizarAnimJog(false, false, false, false, "ataque");
			}
			else {
				std::cerr << "Nao eh possivel atualizar a animacao pois o animador eh NULL" << std::endl;
			}
		}

	}

}
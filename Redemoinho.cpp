#include "Redemoinho.h"

namespace Entidades {

	namespace Obstaculos {

		Redemoinho::Redemoinho() :
			Obstaculo(),
			raio(120),
			danosidade(20),
			dano_unico(false)
		{
			intransponivel = false;
			danoso = true;
			corpo = new sf::RectangleShape(sf::Vector2f(raio, raio));
			if (corpo) {
				corpo->setPosition(150.0, ALTURA_TELA - 50 - raio);	// 50 Seria o tamanho do chão
			}

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 10.0f, corpo->getSize().y));
			if (hitBox) {
				hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2) - 08.0f,
									corpo->getPosition().y);
			}

			inicializaAnimacoes();
		}

		Redemoinho::~Redemoinho() {
			dano_unico = false;
		}

		void Redemoinho::executar() {
			atualizaAnimacao();
			if (animador->getImgAtual() < 5 || animador->getImgAtual() > 10) {
				dano_unico = true;
				danoso = false;
			}
			else {
				danoso = true;
			}

			sofrerContraForca();

		}

		void Redemoinho::obstaculizar(Personagens::Jogador* p) {
			if (p) {
				if (dano_unico && danoso) {
					p->diminuiVida(danosidade);
					dano_unico = false;
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel diminuir a vida pois o jogador eh NULL" << std::endl;
			}
		}

		void Redemoinho::salvar() {
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_redemoinhos.push_back(buffer);
		}

		void Redemoinho::salvarDataBuffer(nlohmann::json& buffer) {
			Obstaculo::salvarDataBuffer(buffer);

			buffer["raio"] = raio;
			buffer["danosidade"] = danosidade;
			buffer["dano_unico"] = dano_unico;
		}

		void Redemoinho::inicializaAnimacoes() {
			if (corpo) {
				setAnimador(corpo);
				if (animador) {
					animador->addAnimacao("Imagens/Obstaculos/redemoinho.png", "ataque", 13, 0.13, sf::Vector2f(1.0f, 1.0f));
				}
			}
			else {
				std::cerr << "Nao eh possivel inicializar a animacao pois o corpo eh NULL" << std::endl;
			}
		}

		void Redemoinho::atualizaAnimacao() {
			if (animador) {
				animador->atualizarAnim(false, false, "ataque");
			}
			else {
				std::cerr << "Nao eh possivel atualizar a animacao pois o animador eh NULL" << std::endl;
			}
		}

		void Redemoinho::carregar(const nlohmann::json& j) {
			try {
				dano_unico = j.at("dano_unico").get<bool>();
			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Chave 'dano_unico' ausente." << e.what() << std::endl;
			}

			Obstaculo::carregar(j);
		}

	}

}
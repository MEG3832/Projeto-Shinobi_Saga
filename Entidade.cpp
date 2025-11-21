#include "Entidade.h"

namespace Entidades {

	nlohmann::json Entidade::buffer_plataformas = nlohmann::json::array();
	nlohmann::json Entidade::buffer_redemoinhos = nlohmann::json::array();
	nlohmann::json Entidade::buffer_tengus = nlohmann::json::array();
	nlohmann::json Entidade::buffer_samurais = nlohmann::json::array();
	nlohmann::json Entidade::buffer_kitsunes = nlohmann::json::array();
	nlohmann::json Entidade::buffer_armadilhas = nlohmann::json::array();
	nlohmann::json Entidade::buffer_projeteis = nlohmann::json::array();
	nlohmann::json Entidade::buffer_jogadores = nlohmann::json::array();

	nlohmann::json Entidade::getArrayPlataformas() {
		return buffer_plataformas;
	}

	nlohmann::json Entidade::getArrayRedemoinhos() {
		return buffer_redemoinhos;
	}

	nlohmann::json Entidade::getArrayTengus() {
		return buffer_tengus;
	}

	nlohmann::json Entidade::getArraySamurais() {
		return buffer_samurais;
	}

	nlohmann::json Entidade::getArrayArmadilhas() {
		return buffer_armadilhas;
	}

	nlohmann::json Entidade::getArrayKitsunes() {
		return buffer_kitsunes;
	}

	nlohmann::json Entidade::getArrayProjeteis() {
		return buffer_projeteis;
	}

	nlohmann::json Entidade::getArrayJogadores() {
		return buffer_jogadores;
	}

	void Entidade::limparBuffers() {

		buffer_plataformas = {};
		buffer_redemoinhos = {};
		buffer_tengus = {};
		buffer_samurais = {};
		buffer_armadilhas = {};
		buffer_kitsunes = {};
		buffer_projeteis = {};
		buffer_jogadores = {};

	}

	//Criar o corpo aqui já, na construtora de Entidade
	Entidade::Entidade() : 
		Ente(),
		pos(0.0, 0.0),
		veloc(0.0, 0.0),
		animador(nullptr),
		intransponivel(true)
	{}

	Entidade::~Entidade()
	{
		if (animador) {
			delete animador;
			animador = nullptr;
		}
	}

	sf::Vector2f Entidade::getPos() {	// Não é mais fácil retornar o position direto?
		if(corpo) {
			sf::Vector2f position(corpo->getPosition());
			pos.x = position.x;
			pos.y = position.y;
			return pos;
		}
		else {
			std::cerr << "ERRO: Nao eh possivel retornar a posicao do corpo pois ele eh NULL" << std::endl;
		}
	}

	void Entidade::setAnimador(sf::RectangleShape* body) {
		if (!animador) {
			animador = new Animadores::Animacao(body);
		}
	}

	//Animadores::Animacao* Entidade::getAnimador()
	//{
		//return animador;
	//}

	bool Entidade::getIntransponivel() {
		return intransponivel;
	}

	void Entidade::setIntransponivel(bool intangivel) {
		intransponivel = intangivel;
	}

	void Entidade::sofrerGravidade() {
		veloc.y += GRAVIDADE;
		corpo->move(0.0, veloc.y);
		hitBox->move(0.0, veloc.y);
	}

	void Entidade::carregar(const nlohmann::json& j) {
		try {
			if (corpo) {
				corpo->setPosition(j.at("posX").get<float>(), j.at("posY").get<float>());
			}
			if (hitBox) {
				hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
								    corpo->getPosition().y);
			}
			// Nao vou fazer com size pois todo corpo tem um temanho setado na construtora

			veloc.x = j.at("velocX").get<float>();
			veloc.y = j.at("velocY").get<float>();

			if (animador) {
				animador->setEstadoAtual(j.at("EstadoAtual_animacao").get<std::string>());
				animador->setImgAtual(j.at("ImagemAtual_animacao").get<int>());
				animador->setTempoTotal(j.at("TempoTotal_animacao").get<float>());
			}

			intransponivel = j.at("intransponivel").get<int>();
			
		}
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: Alguma das chaves estah ausente." << e.what() << std::endl;
		}
	}

	void Entidade::salvarDataBuffer(nlohmann::json& buffer) {
		if (animador) {
			buffer["ImagemAtual_animacao"] = animador->getImgAtual();
			buffer["TempoTotal_animacao"] = animador->getTempoTotal();
			buffer["EstadoAtual_animacao"] = animador->getEstadoAtual();
		}
		buffer["velocX"] = veloc.x;
		buffer["velocY"] = veloc.y;
		buffer["posX"] = corpo->getPosition().x;
		buffer["posY"] = corpo->getPosition().y;
		buffer["intransponivel"] = intransponivel;
	}
}
#include "Entidade.h"

namespace Entidades {

	nlohmann::json Entidade::buffer_plataformas = nlohmann::json::array();
	nlohmann::json Entidade::buffer_redemoinhos = nlohmann::json::array();

	nlohmann::json Entidade::getArrayPlataformas() {
		return buffer_plataformas;
	}

	nlohmann::json Entidade::getArrayRedemoinhos() {
		return buffer_redemoinhos;
	}

	//Criar o corpo aqui já, na construtora de Entidade
	Entidade::Entidade() : 
		Ente(),
		pos(0.0, 0.0),
		veloc(0.0, 0.0),
		animador(nullptr),
		intransponivel(true)
	{}

	Entidade::~Entidade() {}

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
		animador = new Animadores::Animacao(body);
	}

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
#include "Entidade.h"

namespace Entidades {
	//Criar o corpo aqui já, na construtora de Entidade
	Entidade::Entidade() : Ente(), pos(0.0, 0.0)
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
}
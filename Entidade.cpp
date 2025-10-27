#include "Entidade.h"

<<<<<<< HEAD
namespace Entidades {
	//Criar o corpo aqui já, na construtora de Entidade
	Entidade::Entidade() : Ente(), pos(0.0, 0.0)
	{}
=======
Entidade::Entidade(): veloc(0.0,0.0), body(sf::Vector2f(120.0,260.0))
{
}
>>>>>>> animation

	Entidade::~Entidade() {}

<<<<<<< HEAD
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
=======
sf::RectangleShape Entidade::getBody()
{
	return body;
}

//void Entidade::executar()
//{
//}

//void Entidade::salvar()
//{
//}

void Entidade::desenhar()
{
	pGG->desenharEnte(*pFig);
>>>>>>> animation
}
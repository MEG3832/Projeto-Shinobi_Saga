#include "Ente.h"

Gerenciadores::Gerenciador_Grafico* Ente::pGG = pGG->getGerenciadorGrafico();

void Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG) {	// Não utilizamos
	pGG = pG;
}

Ente::Ente() :
	corpo(nullptr),
	hitBox(nullptr)
{}

Ente::~Ente() // Como o Gerenciador Gráfico não é criado aqui, não podemos deletá-lo em Ente
{
	if (corpo) {
		delete corpo;
		corpo = nullptr;
	}

	if (hitBox) {
		delete hitBox;
		hitBox = nullptr;
	}
}

void Ente::desenhar() {	// Por ser virtual (o que eu não sei se pode), por enquanto não faz nada
	pGG->desenharEnte(this);
}

sf::RectangleShape* Ente::getCorpo() {
	return corpo;
}

sf::RectangleShape* Ente::getHitBox() {
	return hitBox;
}
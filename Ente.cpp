#include "Ente.h"

Gerenciador_Grafico* Ente::pGG = pGG->getGerenciadorGrafico();

void Ente::setGG(Gerenciador_Grafico* pG) {	// Não utilizamos
	pGG = pG;
}

Ente::Ente() :
	pFig(new sf::RectangleShape(sf::Vector2f(120.0, 260.0)))	// Exemplo
{}

Ente::~Ente() // Como o Gerenciador Gráfico não é criado aqui, não podemos deletá-lo em Ente
{}

void Ente::desenhar() {	// Por ser virtual (o que eu não sei se pode), por enquanto não faz nada
	pGG->desenharEnte(*pFig);
}

#include "Ente.h"

Gerenciadores::Gerenciador_Grafico* Ente::pGG = pGG->getGerenciadorGrafico();

void Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG) {	// Não utilizamos
	pGG = pG;
}

Ente::Ente() :
	pFig(new sf::CircleShape(100.f))	// Exemplo
{}

Ente::~Ente() // Como o Gerenciador Gráfico não é criado aqui, não podemos deletá-lo em Ente
{}

void Ente::desenhar() {	// Por ser virtual (o que eu não sei se pode), por enquanto não faz nada
	pGG->desenharEnte(*pFig);
}

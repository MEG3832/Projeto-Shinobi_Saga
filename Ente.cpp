#include "Ente.h"

Gerenciador_Grafico* Ente::pGG = nullptr;

void Ente::setGG(Gerenciador_Grafico* pG) {
	pGG = pG;
}

Ente::Ente() :
	pFig(new sf::CircleShape(100.f))
{}

Ente::~Ente() {
	delete pGG;
	pGG = nullptr;
	pFig = nullptr;
}

void Ente::desenhar() {
	pGG->desenharEnte(*pFig);
}

#include "Ente.h"

Gerenciador_Grafico* Ente::pGG = nullptr;

void Ente::setGG(Gerenciador_Grafico* pG) {
	pGG = pG;
}

Ente::Ente()
{}

Ente::~Ente() {}

void Ente::desenhar() {
	return;
}

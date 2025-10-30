#include "Ente.h"

Gerenciadores::Gerenciador_Grafico* Ente::pGG = pGG->getGerenciadorGrafico();

void Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG) {	// Não utilizamos
	pGG = pG;
}

Ente::Ente() :
	corpo(nullptr)
{}

Ente::~Ente() // Como o Gerenciador Gráfico não é criado aqui, não podemos deletá-lo em Ente
{
	if(corpo) {
		delete corpo;
	}
	corpo = nullptr;
}

void Ente::desenhar() {	// Por ser virtual (o que eu não sei se pode), por enquanto não faz nada
	pGG->desenharEnte(*corpo);
}

sf::Vector2f Ente::getTam() {
	if(corpo) {
		return corpo->getSize();
	}
	else {
		std::cerr << "ERRO: Nao eh possivel retornar o tamanho do corpo pois ele eh NULL" << std::endl;
	}
}

sf::RectangleShape* Ente::getCorpo() {
	return corpo;
}
#include "Entidade.h"

Entidade::Entidade(): veloc(0.0,0.0), body(sf::Vector2f(120.0,260.0))
{
}

Entidade::~Entidade() { }

sf::RectangleShape Entidade::getBody()
{
	return body;
}

void Entidade::executar()
{
}

void Entidade::salvar()
{
}

void Entidade::desenhar()
{
	pGG->desenharEnte(body);
}
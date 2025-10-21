#include "Entidade.h"

Entidade::Entidade(): veloc(0.0,0.0), body(sf::Vector2f(10.0,10.0))
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
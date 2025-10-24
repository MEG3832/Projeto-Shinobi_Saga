#pragma once

#include "Header.h"
#include "Ente.h"


class Entidade:public Ente
{
protected:

	//ostream buffer; ->implementar
	sf::Vector2f veloc;
	sf::RectangleShape body;

protected:

	//void salvarDataBuffer(); ->implementar
	
public:

	Entidade();
	virtual ~Entidade();
	sf::RectangleShape getBody();
	virtual void executar() = 0;
	virtual void salvar() = 0;
	virtual void desenhar();
	//...

};


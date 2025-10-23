#pragma once

#include "Header.h"
#include "Ente.h"


class Entidade:public Ente
{
protected:

	//ostream buffer; ->implementar
	sf::Vector2f pos;

protected:

	//void salvarDataBuffer(); ->implementar
	
public:

	Entidade();
	virtual ~Entidade();
	virtual void executar() = 0;
	virtual void salvar() = 0;
	//...

};


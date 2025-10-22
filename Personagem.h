#pragma once

#include "Header.h"
#include "Entidade.h"

class Personagem:public Entidade
{

protected:

	int num_vidas;
	//sf::Vector2f veloc;
	//...

public:

	Personagem();
	~Personagem();
	//void salvarDataBuffer();
	virtual void executar();
	virtual void salvar();
	virtual void mover();


};


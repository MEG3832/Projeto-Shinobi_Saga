#pragma once

#include "Ente.h"

namespace Entidades {

	class Entidade :public Ente
	{
	protected:

		//ostream buffer; ->implementar
		sf::Vector2f pos;	// Qual o sentido de ter pos?

	protected:

		//void salvarDataBuffer(); ->implementar

<<<<<<< HEAD
	public:
=======
	Entidade();
	virtual ~Entidade();
	sf::RectangleShape getBody();
	//virtual void executar() = 0;
	//virtual void salvar() = 0;
	virtual void desenhar();
	//...
>>>>>>> animation

		Entidade();
		virtual ~Entidade();
		virtual void executar() = 0;
		virtual void salvar() = 0;
		sf::Vector2f getPos();
		//...

	};

}
#pragma once

#include "Animacao.h"
#include "Ente.h"

namespace Entidades {

	class Entidade :public Ente
	{
	protected:

		//ostream buffer; ->implementar
		sf::Vector2f pos;	// Qual o sentido de ter pos?
		sf::Vector2f veloc;
		Animadores::Animacao* animador;
		bool intransponivel;

	protected:

		//void salvarDataBuffer(); ->implementar

	public:

		Entidade();
		virtual ~Entidade();
		virtual void executar() = 0;
		virtual void salvar() = 0;
		sf::Vector2f getPos(); // Isso estah inutil, posso tirar? Assim como o atributo posição
		void setAnimador(sf::RectangleShape* body);
		bool getIntransponivel();
		void setIntransponivel(bool intangivel);
		void sofrerGravidade();
		//...

	};

}
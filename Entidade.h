#pragma once

#include "Animacao.h"
#include "Ente.h"

namespace Entidades {

	class Entidade :public Ente
	{
		protected:

			//ostream buffer; ->implementar
			sf::Vector2f pos;	// Nao estou usando, pois corpo->getPosition() eh equivalente

			// Variavies
			sf::Vector2f veloc;
			Animadores::Animacao* animador;
			bool intransponivel;

			//void salvarDataBuffer(); ->implementar

		public:

			Entidade();
			virtual ~Entidade();

			void setAnimador(sf::RectangleShape* body);
			bool getIntransponivel();
			void setIntransponivel(bool intangivel);
			void sofrerGravidade();
			sf::Vector2f getPos(); // Nao usei, posso tirar? corpo->getPosition() eh equivalente

			// Abstratas
			virtual void executar() = 0;
			virtual void salvar() = 0;


	};

}
#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class Samurai_Inimigo : public Inimigo
		{
		private:
			float tamanho; // pegamos o tamanho em x do corpo do inimigo.

		public:
			Samurai_Inimigo(Jogador* pJ, sf::Vector2f pos, sf::Vector2f tam);
			~Samurai_Inimigo();

			// Implementação dos métodos virtuais da base
			void mover();
			void danificar(Jogador* pJ); // Dano no jogador
			void inicializaAnimacoes();

			// Sobrescreve o empurrão
			void empurrar(Jogador* pJ);


			void executar();
		};
	}
}
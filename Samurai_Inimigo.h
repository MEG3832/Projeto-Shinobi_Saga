#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class Samurai_Inimigo : public Inimigo
		{
		private:
			float resistencia;

		public:
			Samurai_Inimigo(Jogador* pJ, float resist);
			~Samurai_Inimigo();

			// Implementação dos métodos virtuais da base
			void mover();
			void danificar(Jogador* pJ); // Dano no jogador
			void inicializaAnimacoes();

			void diminuiVida(float dano);

			//void empurrar(Jogador* pJ); -> igual ao da base


			void executar();
		};
	}
}
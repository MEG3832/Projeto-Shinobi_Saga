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

			// (re)implementação dos métodos virtuais da base
			void mover();
			void danificar(Jogador* pJ); // dano no jogador
			void inicializaAnimacoes();

			void diminuiVida(int dano);

			//void empurrar(Jogador* pJ); -> igual ao da base


			void executar();
		};
	}
}
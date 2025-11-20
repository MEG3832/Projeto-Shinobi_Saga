#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class Samurai_Inimigo : public Inimigo
		{
		private:
			float cooldownEmpurrao;
			
			// Variaveis
			sf::Clock timer;
			float resistencia;
			bool empurra;

		public:
			Samurai_Inimigo(Jogador* pJ1, Jogador* pJ2, float resist);
			~Samurai_Inimigo();
			void executar();

			// Reimplementacao
			void mover();
			void salvar();
			void danificar(Jogador* pJ); // dano no jogador
			void inicializaAnimacoes();
			void diminuiVida(float dano);

		};
	}
}
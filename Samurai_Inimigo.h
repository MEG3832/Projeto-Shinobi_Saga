#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class Samurai_Inimigo : public Inimigo
		{
		private:
			float cooldownEmpurrao;
			sf::Clock timer;
			
			// Variaveis
			float dt;
			float resistencia;
			bool empurra;

		public:
			Samurai_Inimigo(Jogador* pJ = nullptr, float resist = 0.0);
			~Samurai_Inimigo();
			void executar();

			// Reimplementacao
			void mover();
			void salvar();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);
			void danificar(Jogador* pJ); // dano no jogador
			void inicializaAnimacoes();
			void diminuiVida(int dano);

		};
	}
}
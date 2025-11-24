#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class Samurai : public Inimigo
		{
		private:
			float cooldownEmpurrao;
			sf::Clock timer;
			
			// Variaveis
			float dt;
			float resistencia;
			bool empurra;

		public:
			Samurai(Jogador* pJ1, Jogador* pJ2, float resist);
			~Samurai();
			void executar();

			// Reimplementacao
			void mover();
			void salvar();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);
			void danificar(Jogador* pJ); // dano no jogador
			void inicializaAnimacoes();
			void diminuiVida(float dano);

		};
	}
}
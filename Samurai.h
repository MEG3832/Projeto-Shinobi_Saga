/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class Samurai : public Inimigo
		{
		private:
			const float cooldownEmpurrao;
			sf::Clock timer;
			
			// Variaveis
			float dt;
			float resistencia;
			bool empurra;

			void inicializaAnimacoes();

		public:
			Samurai(Jogador* pJ1 = nullptr, Jogador* pJ2 = nullptr, float resist = 0.0);
			~Samurai();

			void executar();

			// Reimplementacao
			void mover();
			void salvar();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);
			void danificar(Jogador* pJ); // dano no jogador
			void diminuiVida(float dano);

		};
	}
}
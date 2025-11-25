/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once
#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		class Armadilha_de_urso :  public Obstaculo
		{
		private:
			const float lado;
			short int danosidade;
			const float cooldown_atordoamento;
			sf::Clock timer;
			
			// Variaveis
			float dt;	// Nao testei essa mudanca do dt

			void atualizaAnimacao();
			void inicializaAnimacoes();

		public:
			Armadilha_de_urso();
			~Armadilha_de_urso();
		
			void carregar(const nlohmann::json& j);
			void salvarDataBuffer(nlohmann::json& buffer);

			// Reimplementacoes
			void executar();
			void obstaculizar(Personagens::Jogador* pJ);
			void salvar();
		};

	}

}
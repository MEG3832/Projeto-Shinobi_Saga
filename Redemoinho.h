/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Redemoinho : public Obstaculo
		{
		private:
			const float raio;
			const float danosidade;

			// Variaveis
			bool dano_unico;


			void inicializaAnimacoes();
			void atualizaAnimacao();


		public:
			Redemoinho();
			~Redemoinho();

			void executar();
			void obstaculizar(Personagens::Jogador* p);

			void salvar();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);
		};

	}

}
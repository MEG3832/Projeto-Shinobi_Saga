/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
			protected:

				// Variaveis
				bool danoso;

				virtual void carregar(const nlohmann::json& j);

			public:
				Obstaculo();
				virtual ~Obstaculo();

				void salvarDataBuffer(nlohmann::json& buffer);
				virtual void sofrerContraForca();

				// Abstratas
				virtual void executar() = 0;
				virtual void salvar() = 0;
				virtual void obstaculizar(Personagens::Jogador* pJ) = 0;
		};

	}

}
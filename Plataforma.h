/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Plataforma : public Obstaculo
		{
			private:	// Tirar altura e comprimento e colocar um atributo que individualize 
				int altura;
				int comprimento;
				sf::Texture textura;
				int cura;

			public:
				Plataforma(int id = 1);
				~Plataforma();
				void executar();
				void obstaculizar(Personagens::Jogador* p);
				void salvar();
				void salvarDataBuffer(nlohmann::json& buffer);
				void carregar(const nlohmann::json& j);
		};

	}

}
/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once

#include "Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		class Jogador;

		class Tengu : public Inimigo
		{
			private:

				const float raio_perseg;

				void inicializaAnimacoes();
				void perseguir(Jogador* pJ);


			public:

				Tengu(Jogador* pJ1 = nullptr, Jogador* pJ2 = nullptr);
				~Tengu();

				void atacar(Jogador* pJ); //implementa a investida do tengu

				// Reimplementacoes
				void executar();
				void danificar(Jogador* pJ);
				void mover();
				void salvar();
				void salvarDataBuffer(nlohmann::json& buffer);
				void carregar(const nlohmann::json& j);
				void diminuiVida(int dano);

		};

	}
}


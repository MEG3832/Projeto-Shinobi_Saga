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

				float raio_perseg;

			public:

				Tengu(Jogador* pJ);
				~Tengu();
				void atacar(Jogador* pJ); //implementa a investida do tengu

				// Reimplementacoes
				void executar();
				void danificar(Jogador* pJ);
				void perseguir(Jogador* pJ);
				void mover();
				void salvar();
				void inicializaAnimacoes();

		};

	}
}


#pragma once

#include "Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		class Jogador;

		class Tengu : public Inimigo
		{
		//private:

			float raio_perseg;


		public:

			Tengu(Jogador* pJ);
			~Tengu();
			void executar();
			void danificar(Jogador* pJ);
			void perseguir(Jogador* pJ);
			void atacar(Jogador* pJ); //implementa a investida do tengu
			void mover();
			void inicializaAnimacoes();

			// Sobrescreve 'diminuiVida' para aumentar a maldade
			void diminuiVida(int dano); // Dano recebido pelo Tengu

			//void salvar();

		};

	}
}


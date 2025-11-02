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

			bool paraEsq;


		public:

			Tengu(Jogador* pJ);
			~Tengu();
			void executar();
			void danificar(Jogador* pJ);
			//void empurrar(Jogador* pJ); ->igual ao de inimigo
			void perseguir(Jogador* pJ);
			void atacar(Jogador* pJ);

			//void salvar();
			void mover();
			void inicializaAnimacoes();

		};

	}
}


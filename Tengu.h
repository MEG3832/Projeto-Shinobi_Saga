#pragma once

#include "Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		class Jogador;

		class Tengu : public Inimigo
		{
			sf::RectangleShape* espada;


		public:

			Tengu(Jogador* pJ);
			~Tengu();
			void executar();
			void danificar(Jogador* pJ);
			void empurrar(Jogador* pJ);
			void perseguir(Jogador* pJ);
			void salvar();
			void mover();
			void inicializaAnimacoes();

		};

	}
}


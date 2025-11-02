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

			//sf::RectangleShape* espada;
			//bool atacando;
			float cooldownAtaque;
			sf::Clock relogioAtaque; //mede o cooldown
			bool paraEsq;

		public:

			Tengu(Jogador* pJ);
			~Tengu();
			void executar();
			void danificar(Jogador* pJ);
			//void empurrar(Jogador* pJ); ->igual ao de inimigo
			void empurrarForte(Jogador* pJ);
			void perseguir(Jogador* pJ);
			void atacar(Jogador* pJ);
			//void atualizarPosEspada();

			//void salvar();
			//void mover();
			void inicializaAnimacoes();

		};

	}
}


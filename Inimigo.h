#pragma once

#include "Personagem.h"


namespace Entidades {

	namespace Personagens {

		class Jogador;

		class Inimigo : public Personagem
		{
			protected:
				int nivel_maldade;
				float raio_perseg;
				sf::Vector2f veloc;
				Jogador* jogAlvo;

			public:
				Inimigo(Jogador* pJ);
				~Inimigo();
				void salvarDataBuffer();
				virtual void executar();
				virtual void danificar(Jogador* pJ);
				virtual void empurrar(Jogador* pJ);
				virtual void perseguir(Jogador* pJ);
				virtual void salvar();
				virtual void mover();
				virtual void inicializaAnimacoes();
		};

	}

}
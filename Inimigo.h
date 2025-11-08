#pragma once

#include "Personagem.h"


namespace Entidades {

	namespace Personagens {

		class Jogador;

		class Inimigo : public Personagem
		{
			protected:
				int nivel_maldade;
				sf::Vector2f veloc;
				Jogador* jogAlvo;
				bool paraEsq;

				//tratam da ação de atacar: (Tengu e Kitsune usam)

				float cooldownAtaque;
				sf::Clock relogioAtaque; //mede o cooldown

				//tratam da ação de andar:

				bool andando;
				sf::Clock relogioAndar;
				float tempoAndar;

				
				// Nova função de comportamento base
				void perambular();


			public:

				//construtora e destrutora
				Inimigo(Jogador* pJ);
				virtual ~Inimigo(); //destrutora virtual **
				
				//------//

				virtual void executar() = 0;
				void salvarDataBuffer();
				virtual void salvar();

				//classes filhas (inimigos específicos) vão reimplementar:

				virtual void danificar(Jogador* pJ) = 0;
				virtual void mover() = 0;
				virtual void inicializaAnimacoes() = 0;

				// Métodos com implementação base, mas que podem ser sobrescritos
				virtual void empurrar(Jogador* pJ);

				// Sobrescreve o método da classe Personagem (assumindo que ela exista lá)
				// Usado quando o INIMIGO recebe dano
				virtual void diminuiVida(int dano);

		};

	}

}
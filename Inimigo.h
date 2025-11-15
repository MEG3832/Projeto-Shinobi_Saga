#pragma once

#include "Personagem.h"


namespace Entidades {

	namespace Personagens {

		class Jogador;

		class Inimigo : public Personagem
		{

			protected:
				enum Estado {
					PARADO,
					ANDANDO,
					FERIDO,
					MORRENDO
				};

				float cooldownAtaque;
				float tempoAndar;
				float cooldownAtordoado; //p/ duração da animação "Ferido"

				// Variaveis
				Jogador* jogAlvo;	// Eh uma variavel?
				sf::Clock relogioAtaque; //mede o cooldown
				sf::Clock relogioAndar;
				sf::Clock relogioAtordoado; //mede o cooldown
				int nivel_maldade;
				Estado estado_atual;

				void perambular();
				virtual void empurrar(Jogador* pJ);


			public:

				Inimigo(Jogador* pJ);
				virtual ~Inimigo(); //destrutora virtual **
				void salvarDataBuffer();
				
				// Metodos virtuais puros
				virtual void executar() = 0;
				virtual void salvar() = 0;
				virtual void danificar(Jogador* pJ) = 0;
				virtual void mover() = 0;
				virtual void inicializaAnimacoes() = 0;

				// Reimplementacoes
				virtual void diminuiVida(int dano); //para diminuir a vida do inimigo!
				void morrer();
				bool getFerido();
				bool getMorto();
		};

	}

}
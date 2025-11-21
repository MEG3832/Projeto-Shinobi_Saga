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
				sf::Clock relogioAtaque; 
				sf::Clock relogioAndar;
				sf::Clock relogioAtordoado; 
				Jogador* jogAlvo;	// Eh uma variavel?

				// Variaveis
				int nivel_maldade;
				float dt_ataque;
				float dt_andar;
				float dt_atordoamento;
				Estado estado_atual;

				void perambular();
				virtual void empurrar(Jogador* pJ);


			public:

				Inimigo(Jogador* pJ);
				virtual ~Inimigo(); //destrutora virtual **
				void salvarDataBuffer(nlohmann::json& buffer);
				void carregar(const nlohmann::json& buffer);
				
				// Metodos virtuais puros
				virtual void executar() = 0;
				virtual void salvar() = 0;
				virtual void danificar(Jogador* pJ) = 0;
				virtual void mover() = 0;
				virtual void inicializaAnimacoes() = 0;

				// Reimplementacoes
				virtual void diminuiVida(int dano); // A pontuacao do jogador esta aumentando com um valor estatico
				void morrer();
				bool getFerido();
				bool getMorto();
		};

	}

}
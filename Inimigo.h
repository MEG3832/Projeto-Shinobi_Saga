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

				Jogador* pJogador1; // armazena referência fixa ao J1
				Jogador* pJogador2; // armazena referência fixa ao J2 (pode ser nullptr)
				Jogador* jogAlvo;   // o ponteiro que muda para onde aponta dependendo da distância

				// Variaveis
				int nivel_maldade;
				float dt_ataque;
				float dt_andar;
				float dt_atordoamento;
				Estado estado_atual;

				void perambular();
				virtual void empurrar(Jogador* pJ);

				void atualizarAlvo(); // Nova função!


			public:

				Inimigo(Jogador* pJ1, Jogador* pJ2 = nullptr);
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

				void setJogAlvo(Jogador* pJog);
				virtual void diminuiVida(int dano); //para diminuir a vida do inimigo!
				void morrer();
				bool getFerido();
				bool getMorto();
		};

	}

}
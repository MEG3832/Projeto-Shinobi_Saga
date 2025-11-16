#pragma once
// A forma como eu estou setando a posicao inicial do personagem estah muito feia
#include "Personagem.h"
#include "Header.h"


namespace Entidades {

	namespace Personagens {

		class Inimigo;

		class Jogador : public Personagem
		{
			protected:

				enum Estado {
					PARADO,	// E andando
					CORRENDO,
					ANDANDO,
					ATACANDO,
					DEFENDENDO,
					PULANDO,	
					ATORDOADO,	// Não testei
					PREPARANDO_PULO,
					FERIDO,
					MORRENDO
				};

				float cooldown_ataque;
				float cooldown_pulo;
				float cooldown_dano;
				float velPulo;
				sf::RectangleShape* hitboxAtaque;
				sf::Vector2f velocKnockBack;
				sf::Clock timer;

				// Variaveis
				int pontos;
				int id; // 1 ou 2
				float dt;
				Estado estado_atual;
				sf::Vector2f direcao;

			public:

				Jogador(const int ident); //com parâmetro
				Jogador(); // sem parâmetro
				~Jogador();
				void colidir(Inimigo* pIn);
				void setVelKnockBack(sf::Vector2f velKB);
				void setDirecao(sf::Vector2f dir);
				void atualizaAnimacao();	// Fazer virtual em Personagem
				void setAtordoado(bool atordoar); // Fazer virtual em Personagem
				void correr(bool correr);
				void atacar();
				bool getAtacando();
				void pular();
				bool getSubindo();
				void setDefesa(bool defender);
				bool protegendo();
				void diminuiVida(float dano);	// Fazer virtual em Personagem
				void ferir();
				void atualizarHitboxAtaque();
				sf::RectangleShape* getHitboxAtaque() const;

				// Reimplementacao
				void executar();
				void salvar();
				void mover(); //nota! o método mover lida com toda a parte do "knockBack" causado pelo inimigo
				void inicializaAnimacoes();
				void setNoChao();
				void morrer();
				bool getFerido();
				bool getMorto();
		};

	}

}
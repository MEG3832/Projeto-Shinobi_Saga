/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once
// A forma como eu estou setando a posicao inicial do personagem estah muito feia
#include "Personagem.h"
#include "Header.h"


namespace Entidades {

	namespace Personagens {

		class Inimigo;

		class Jogador : public Personagem
		{
			private:

				void inicializaAnimacoes();
				void atualizaAnimacao();	// Fazer virtual em Personagem


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

				const float cooldown_ataque;
				const float cooldown_pulo;
				const float cooldown_dano;
				const float tempo_morte;
				float velPulo;
				sf::RectangleShape* hitboxAtaque;
				sf::Clock timer;

				// Variaveis
				int pontos;
				int id; // 1 ou 2
				float dt;
				Estado estado_atual;
				sf::Vector2f direcao;
				sf::Vector2f velocKnockBack;

			public:

				Jogador(const int ident = 1);
				~Jogador();

				void colidir(Inimigo* pIn);
				void setVelKnockBack(sf::Vector2f velKB);
				void setDirecao(sf::Vector2f dir);
				void setAtordoado(bool atordoar);
				void correr(bool correr);
				void atacar();
				bool getAtacando();
				void pular();
				bool getSubindo();
				void setDefesa(bool defender);
				bool protegendo();
				void diminuiVida(float dano);	// Fazer virtual em Personagem
				void curar(int cura);
				void restaurarVida();
				void ferir();
				void atualizarHitboxAtaque();
				sf::RectangleShape* getHitboxAtaque() const;
				int getPontuacao();
				void aumentaPontuacao(int num);
				bool podeSeguirPorMorte();
				void carregar(const nlohmann::json& j);
				void salvarDataBuffer(nlohmann::json& buffer);

				// Reimplementacao
				void executar();
				void salvar();
				void mover(); //nota! o método mover lida com toda a parte do "knockBack" causado pelo inimigo
				void setNoChao();
				void morrer();
				bool getFerido();
				bool getMorto();
		};

	}

}
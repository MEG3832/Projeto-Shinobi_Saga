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

			int pontos;
			bool paraEsq;
			bool pulando;
			bool caindo;
			bool atordoado;
			bool correndo;
			bool atacando;
			bool parado;
			bool noChao;
			float dt;
			sf::Clock timer;
			float cooldown_ataque;
			float cooldown_pulo;
			bool preparandoPulo;
			float velPulo;

			//irão tratar da alteração do hitbox do jogador quando estiver atacando...
			sf::RectangleShape* hitboxAtaque; // hitbox específica para ataques
			bool hitboxAtaqueAtiva;


			sf::Vector2f velocKnockBack;
			int id; // 1 ou 2
			sf::Vector2f direcao;

		public:

			Jogador(const sf::Vector2f pos, const int ident = 1); //com parâmetro
			Jogador(); // sem parâmetro
			~Jogador();
			void colidir(Inimigo* pIn);
			//void atacar();
			void executar();
			void salvar();
			void mover(); //nota! o método mover lida com toda a parte do "knockBack" causado pelo inimigo
			void setVelKnockBack(sf::Vector2f velKB);
			void setDirecao(sf::Vector2f dir);
			void inicializaAnimacoes();
			void atualizaAnimacao();
			void setAtordoado(bool atordoar);
			void correr(bool correr);
			void atacar();
			bool getAtacando();
			void aplicarForcaNormal();
			void pular();
			void setNoChao(bool noChao);
			bool getSubindo();
			bool getCaindo();
			void setCair(bool cair);

			void atualizarHitboxAtaque();
			sf::RectangleShape* getHitboxAtaque() const { return hitboxAtaque; }
			bool getHitboxAtaqueAtiva() const { return hitboxAtaqueAtiva; }

		};

	}

}
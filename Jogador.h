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
			bool subindo;
			bool caindo;
			bool correndo;
			
			sf::Vector2f veloc;
			sf::Vector2f velocKnockBack;
			int id; // 1 ou 2
			sf::Vector2f direcao;
			int num;

		public:

			Jogador(const sf::Vector2f pos, const int ident = 1); //com parâmetro
			Jogador(); // sem parâmetro
			~Jogador();
			void colidir(Inimigo* pIn);
			//void atacar();
			void executar();
			void salvar();
			void mover(); //nota! o método mover lida com toda a parte do "knockBack" causado pelo inimigo
			void diminuiVida(int nv_maldade);
			int getVida();
			void setVelKnockBack(sf::Vector2f velKB);
			void setDirecao(sf::Vector2f dir);
			void inicializaAnimacoes();
			void atualizaAnimacao();
		};

	}

}
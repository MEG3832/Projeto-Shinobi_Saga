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

			//!!!!!!!!talvez rastrear esse tipo de coisa apenas para o jogador...
			bool paraEsq;
			bool subindo;
			bool caindo;
			bool atordoado;
			
			sf::Vector2f veloc;
			int id; // 1 ou 2
			char direcao;

		public:

			Jogador(const sf::Vector2f pos, const int ident = 1); //com parâmetro
			Jogador(); // sem parâmetro
			~Jogador();
			void colidir(Inimigo* pIn);
			//void atacar();
			void executar();
			void salvar();
			void mover();
			int getVida();
			void setDirecao(const char direcao);
			char getDirecao();
			void inicializaAnimacoes();
			void atualizaAnimacao();
			void setAtordoado(bool atordoar);
		};

	}

}
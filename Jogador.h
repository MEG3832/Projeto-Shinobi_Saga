#pragma once
// A forma como eu estou setando a posicao inicial do personagem estah muito feia
#include "Personagem.h"
#include "Header.h"

namespace Entidades {

	namespace Personagens {

		class Jogador : public Personagem
		{
		protected:

			int pontos;

			//!!!!!!!!talvez rastrear esse tipo de coisa apenas para o jogador...
			bool paraEsq;
			bool subindo;
			bool caindo;
			
			sf::Vector2f veloc;
			int id; // 1 ou 2
			char direcao;
			int num;
			sf::RectangleShape teste;

		public:

			Jogador(const sf::Vector2f pos, const int ident = 1); //com parâmetro
			Jogador(); // sem parâmetro
			~Jogador();
			void colidir(Entidade* pe);
			void executar();
			void salvar();
			void mover();
			void setDirecao(const char direcao);
			char getDirecao();
			void inicializaAnimacoes();
			void atualizaAnimacao();
		};

	}

}
#pragma once

#include "Personagem.h"
#include "Header.h"

namespace Entidades {

	namespace Personagens {

		class Jogador :public Personagem
		{
		protected:

			sf::Vector2f veloc;
			int pontos;
			int id; // 1 ou 2
			char direcao;
			//...

		public:

			Jogador(const sf::Vector2f pos, const sf::Vector2f tam, const int ident = 1); //com parâmetro
			Jogador(); // sem parâmetro
			~Jogador();
			//void colidir(Inimigo* pIn);
			const sf::RectangleShape* getCorpo();
			void colidir();
			void executar();
			void salvar();
			void mover();
			void setDirecao(const char direcao);
		};

	}

}
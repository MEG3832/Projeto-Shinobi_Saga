#pragma once

#include "Personagem.h"
#include "Header.h"

namespace Entidades {

<<<<<<< HEAD
	namespace Personagens {
=======
	int pontos;

	//!!!!!!!!talvez rastrear esse tipo de coisa apenas para o jogador...
	bool paraEsq;
	bool subindo;
	bool caindo;
		
	//...
>>>>>>> animation

		class Jogador :public Personagem
		{
		protected:

<<<<<<< HEAD
			sf::Vector2f veloc;
			int pontos;
			int id; // 1 ou 2
			char direcao;
			//...
=======
	Jogador(); //com parâmetro
	~Jogador();
	//void colidir(Inimigo* pIn);
	//void executar();
	//void salvar();
	void mover();
	void inicializaAtributos();
	void inicializaAnimacoes();
	void atualizaAnimacao();
	float getDano();
	//...
};
>>>>>>> animation

		public:

			Jogador(const sf::Vector2f pos, const int ident = 1); //com parâmetro
			Jogador(); // sem parâmetro
			~Jogador();
			const sf::RectangleShape* getCorpo();
			void colidir(Entidade* pe);
			void executar();
			void salvar();
			void mover();
			void setDirecao(const char direcao);
		};

	}

}
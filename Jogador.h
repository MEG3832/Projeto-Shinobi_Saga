#pragma once

#include "Personagem.h"
#include "Header.h"

	class Jogador:public Personagem
	{
	protected:

		sf::Vector2f veloc;
		int pontos;
		int id; // 1 ou 2
		//...

	public:

		Jogador(const sf::Vector2f pos, const sf::Vector2f tam, const int ident = 1); //com parâmetro
		Jogador(); // sem parâmetro
		~Jogador();
		//void colidir(Inimigo* pIn);
		const sf::RectangleShape* getCorpo();
		void executar();
		void salvar();
		void mover();
		//...
	};


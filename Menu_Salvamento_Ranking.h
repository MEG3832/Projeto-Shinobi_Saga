#pragma once
#include "Menu.h"

class Menu_Salvamento_Ranking : public Menu
{
	private:

		bool podeSeguir;

		std::string nomeJog;
		std::vector<sf::Text> texto_salvamento;
		Entidades::Personagens::Jogador* pJog1;
		Entidades::Personagens::Jogador* pJog2;

		void inicializaTexto();
		void desenharTexto();
		void salvar();

	public:
		Menu_Salvamento_Ranking();
		~Menu_Salvamento_Ranking();

		void executar();
		void addCaractere(const char c);
		void removeCaractere();
		void setSeguir(bool b);
		void setJogador1(Entidades::Personagens::Jogador* pJ);
		void setJogador2(Entidades::Personagens::Jogador* pJ);
};


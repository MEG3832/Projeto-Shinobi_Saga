#pragma once
#include "Menu.h"

class Menu_Salvamento_Ranking : public Menu
{
	private:

		std::string nomeJog;
		std::vector<sf::Text> texto_salvamento;

		void inicializaTexto();
		void desenharTexto();
		void salvar();

	public:
		Menu_Salvamento_Ranking();
		~Menu_Salvamento_Ranking();

		void executar();
		void addCaractere(const char c);
		void removeCaractere();
};


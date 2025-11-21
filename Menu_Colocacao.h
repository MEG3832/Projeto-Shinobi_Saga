#pragma once
#include "Menu.h"

class Menu_Colocacao : public Menu
{
private:

	std::vector<std::pair<int, std::string>> nomes;
	std::vector<sf::Text> texto_colocacao;
	std::vector<sf::Text> texto_nomes;
	std::vector<sf::Text> texto_pontuacoes;

	int tamanho_rank;

	void inicializaTexto();
	void desenharTexto();

public:
	Menu_Colocacao();
	~Menu_Colocacao();

	void executar();
	void carregar();
};


#pragma once
#include "Header.h"
class Gerenciador_Grafico
{
	private:
		sf::RenderWindow* window;

	public:
		Gerenciador_Grafico();
		~Gerenciador_Grafico();
		void desenharEnte(sf::CircleShape corpo);
		void mostrarEnte();
		sf::RenderWindow* getWindow();
		const bool verificaJanelaAberta();
		void limpaJanela();
		void fecharJanela();
};


#pragma once
#include "Header.h"
class Gerenciador_Grafico
{
	private:
		sf::RenderWindow* window;

		static Gerenciador_Grafico* pGrafico;
		Gerenciador_Grafico();
	public:
		~Gerenciador_Grafico();
		Gerenciador_Grafico* getGerenciadorGrafico();
		void desenharEnte(sf::CircleShape corpo);
		void mostrarEntes();
		sf::RenderWindow* getWindow();
		const bool verificaJanelaAberta();
		void limpaJanela();
		void fecharJanela();
};


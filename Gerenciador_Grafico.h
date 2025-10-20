#pragma once
#include "Header.h"

class Gerenciador_Grafico
{
	#define COMPRIMENTO_TELA 800.0f
	#define ALTURA_TELA 600.0f

	private:
		sf::RenderWindow* window;
		sf::View camera;

		// Padrão de Projeto singleton
		static Gerenciador_Grafico* pGrafico;
		Gerenciador_Grafico();

	public:
		~Gerenciador_Grafico();
		void desenharEnte(sf::CircleShape corpo);
		void mostrarEntes();
		sf::RenderWindow* getWindow();
		const bool verificaJanelaAberta();
		void limpaJanela();
		void fecharJanela();
		sf::View getCamera();
		void atualizaCamera(sf::Vector2f pos);
		sf::Texture carregarTextura(const char* caminhoTextura);

};


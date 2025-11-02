#pragma once
#include "Header.h"
class Ente;

namespace Gerenciadores {

	class Gerenciador_Grafico
	{
		// Mudar para 1920.0f e 1080.0f para tela cheia

	private:
		sf::RenderWindow* window;	// Tamanho da janela
		sf::View camera;	// O que está sendo mostrado

		// Padrão de Projeto singleton (O Gerenciador Gráfico se cria ao dar get)
		static Gerenciador_Grafico* pGrafico;
		Gerenciador_Grafico();

	public:
		~Gerenciador_Grafico();
		Gerenciador_Grafico* getGerenciadorGrafico();
		void desenharEnte(Ente* pE);
		void desenharRect(sf::RectangleShape rect);
		void mostrarEntes();	//Imprime na tela o que foi desenhado
		sf::RenderWindow* getWindow();
		const bool verificaJanelaAberta();
		void limpaJanela();
		void fecharJanela();
		sf::View getCamera();
		void atualizaCamera(sf::Vector2f pos);	// Faz a câmera se mover junto com sua referência (o jogador)
		sf::Texture carregarTextura(const char* caminhoTextura);
	};

}
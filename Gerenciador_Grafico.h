#pragma once
#include "Header.h"

class Gerenciador_Grafico
{
	// Mudar para 1920.0f e 1080.0f para tela cheia
	#define COMPRIMENTO_TELA 800.0f
	#define ALTURA_TELA 600.0f

	private:
		sf::RenderWindow* window;	// Tamanho da janela
		sf::View camera;	// O que está sendo mostrado

		// Padrão de Projeto singleton (O Gerenciador Gráfico se cria ao dar get)
		static Gerenciador_Grafico* pGrafico;
		Gerenciador_Grafico();

		static Gerenciador_Grafico* pGrafico;
		Gerenciador_Grafico();
	public:
		~Gerenciador_Grafico();
		Gerenciador_Grafico* getGerenciadorGrafico();
		void desenharEnte(sf::CircleShape corpo);	// Tem que arrumar. Por enquanto foi usado só no teste inicial
		void mostrarEntes();	//Imprime na tela o que foi desenhado
		sf::RenderWindow* getWindow();
		const bool verificaJanelaAberta();
		void limpaJanela();
		void fecharJanela();
		sf::View getCamera();
		void atualizaCamera(sf::Vector2f pos);	// Faz a câmera se mover junto com sua referência (o jogador)
		sf::Texture carregarTextura(const char* caminhoTextura);

};


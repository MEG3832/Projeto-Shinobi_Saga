#pragma once
#include "Header.h"
#include "Gerenciador_Grafico.h"

/*@@
	
	A classe Imagem fica responsável de tratar a animação de uma textura (aka spritesheet) em específico...

@@*/

namespace Animadores {

	class Imagem
	{
	private:

		Gerenciadores::Gerenciador_Grafico* pGraf;
		sf::Texture textura;
		sf::IntRect retangulo; //a "forma" retangular que vamos colocar a nossa sprite (uma das imagens da spritesheet).
		const sf::Vector2f escala;
		const int qnt_Imagens;
		const float duracao_Frame; //tempo em que a imagem "estática" fica em tela.

		// Variaveis 
		int imag_Atual; //guarda o "índice" da imagem atual (0, 1, 2...)
		float tempo_Total;

	public:

		Imagem(const char* caminhoTextura = nullptr, const int qtd_Img = 0, const float frame_duration = 0.0, const sf::Vector2f scale = sf::Vector2f(1.0, 1.0));
		~Imagem();

		void atualizarFrame(const bool indoParaEsq, const bool rodaUmaVez, const float dt);
		void atualizarFrameProjetil(const bool indoParaEsq, const float dt);
		void resetar();
		const sf::IntRect getRetang();
		const sf::Texture* getTextura();
		const sf::Vector2f getEscala();

		// Usado no salvamento e no carregamento
		const int getImgAtual();
		const float getTempoTotal();
		void setImgAtual(int ia);
		void setTempoTotal(float tt);

	};

}
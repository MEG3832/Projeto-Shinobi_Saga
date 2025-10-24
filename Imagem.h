#pragma once
#include "Header.h"
#include "Gerenciador_Grafico.h"


class Imagem
{

	Gerenciador_Grafico* pGraf;
	sf::Texture textura;
	sf::IntRect retangulo; //a "forma" retangular que vamos colocar a nossa sprite (uma das imagens da spritesheet).
	const sf::Vector2f escala;
	const int qnt_Imagens;
	int imag_Atual; //guarda o "índice" da imagem atual (0, 1, 2...)
	const float duracao_Frame; //tempo em que a imagem "estática" fica em tela.
	float tempo_Total;

public:

	Imagem(const char* caminhoTextura, const int qtd_Img, const float frame_duration, const sf::Vector2f scale);
	~Imagem();


	void atualizar(const bool noAr, const bool indoParaEsq, const float dt);
	void resetar();
	const sf::IntRect getRetang();
	const sf::Texture* getTextura();
	const sf::Vector2f getEscala();

};


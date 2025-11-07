#include "Imagem.h"

namespace Animadores {

	Imagem::Imagem(const char* caminhoTextura, const int qtd_Img, const float frame_duration, const sf::Vector2f scale) :
		pGraf(pGraf->getGerenciadorGrafico()),
		textura(pGraf->carregarTextura(caminhoTextura)),
		retangulo(0, 0, 0, 0),
		escala(scale),
		qnt_Imagens(qtd_Img),
		imag_Atual(0),
		duracao_Frame(frame_duration),
		tempo_Total(0.0)
	{
		retangulo.height = textura.getSize().y; // "altura" da nossa textura
		retangulo.width = (textura.getSize().x) / qnt_Imagens; // largura de cada imagem do spritesheet

	}

	Imagem::~Imagem() {}

	void Imagem::atualizarFrameJog(const bool caindo, const bool subindo, const bool indoParaEsq, const bool rodaUmaVez, const float dt)
	{
		tempo_Total += dt; //guardamos o tempo total para saber se já deu o tempo que queremos que a sprite rode


		if (subindo && tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual++;

			if (imag_Atual >= 7)
				imag_Atual = 6; //trava a imagem
		}

		else if (caindo && tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual = 7;
		}

		else if (rodaUmaVez && tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual++;

			if (imag_Atual >= qnt_Imagens)
				imag_Atual = qnt_Imagens - 1; //para a animação!
		}

		else if (tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual++;

			if (imag_Atual >= qnt_Imagens)
				imag_Atual = 0; //reinicia o spritesheet

		}

		if (indoParaEsq) //invertemos a imagem se estiver indo para a esquerda
		{
			retangulo.left = (imag_Atual + 1) * abs(retangulo.width); // a "leitura" da imagem será feita da direita para a esquerda
			retangulo.width = -abs(retangulo.width);

		}

		else
		{
			retangulo.left = imag_Atual * retangulo.width;
			retangulo.width = abs(retangulo.width);
		}
	}

	void Imagem::atualizarFrameInim(const bool indoParaEsq, const bool rodaUmaVez, const float dt)
	{
		tempo_Total += dt;

		if (rodaUmaVez && tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual++;

			if (imag_Atual >= qnt_Imagens)
				imag_Atual = qnt_Imagens - 1; //pára a animação!
		}

		else if (tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual++;

			if (imag_Atual >= qnt_Imagens)
				imag_Atual = 0; //reinicia o spritesheet

		}

		if (indoParaEsq) //invertemos a imagem se estiver indo para a esquerda
		{
			retangulo.left = (imag_Atual + 1) * abs(retangulo.width); // a "leitura" da imagem será feita da direita para a esquerda
			retangulo.width = -abs(retangulo.width);

		}

		else
		{
			retangulo.left = imag_Atual * retangulo.width;
			retangulo.width = abs(retangulo.width);
		}




	}

	void Imagem::atualizarFrameProjetil(const bool indoParaEsq, const float dt)
	{
		//a animação só irá rodar uma vez mesmo (eu acho?)

		tempo_Total += dt;

		if (tempo_Total >= duracao_Frame)
		{
			tempo_Total = 0.0; //reinicia a contagem de tempo...
			imag_Atual++;

			if (imag_Atual >= qnt_Imagens)
				imag_Atual = qnt_Imagens; //vai até o final da imagem mesmo (é para sumir no final.)
		}

		if (indoParaEsq) //invertemos a imagem se estiver indo para a esquerda
		{
			retangulo.left = (imag_Atual + 1) * abs(retangulo.width); // a "leitura" da imagem será feita da direita para a esquerda
			retangulo.width = -abs(retangulo.width);

		}

		else
		{
			retangulo.left = imag_Atual * retangulo.width;
			retangulo.width = abs(retangulo.width);
		}


	}


	void Imagem::resetar()
	{
		tempo_Total = 0;
		imag_Atual = 0;
	}

	const sf::IntRect Imagem::getRetang() { return retangulo; }

	const sf::Texture* Imagem::getTextura() { return &textura; }

	const sf::Vector2f Imagem::getEscala() { return escala; }

	const int Imagem::getImgAtual()
	{
		return imag_Atual;
	}
}


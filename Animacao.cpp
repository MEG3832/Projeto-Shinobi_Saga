#include "Animacao.h"

namespace Animadores {

	Animacao::Animacao(sf::RectangleShape* body) :
		corpo(body),
		mapImagens(),
		clock(),
		estadoAtual("")
	{


	}

	Animacao::~Animacao() {}

	//atualizar de inimigo e de projetil

	

	void Animacao::atualizarAnimJog(const bool caindo, const bool subindo, const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg)
	{
		if (estadoAtual != estadoImg) //caso o personagem esteja em um estado diferente do atual, resetamos o tempo e o "index" da textura
		{
			estadoAtual = estadoImg;
			mapImagens[estadoAtual]->resetar();
		}

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart(); //reinicia o relógio para guardar o intervalo de tempo...

		Imagem* img = mapImagens[estadoAtual];

		sf::Vector2f tamCorpo = corpo->getSize();
		sf::Vector2f escala = img->getEscala();

		img->atualizarFrameJog(caindo, subindo, indoParaEsq, rodaUmaVez, dt);


		corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
		corpo->setTexture(img->getTextura());
		corpo->setScale(escala.x, escala.y);

	}

	void Animacao::atualizarAnimInim(const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg)
	{
		if (estadoAtual != estadoImg) //caso o personagem esteja em um estado diferente do atual, resetamos o tempo e o "index" da textura
		{
			estadoAtual = estadoImg;
			mapImagens[estadoAtual]->resetar();
		}

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart(); //reinicia o relógio para guardar o intervalo de tempo...

		Imagem* img = mapImagens[estadoAtual];

		sf::Vector2f tamCorpo = corpo->getSize();
		sf::Vector2f escala = img->getEscala();

		img->atualizarFrameInim(indoParaEsq, rodaUmaVez, dt);


		corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
		corpo->setTexture(img->getTextura());
		corpo->setScale(escala.x, escala.y);

	}

	void Animacao::atualizarAnimProjetil(const bool indoParaEsq, std::string estadoUnico)
	{
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart(); //reinicia o relógio para guardar o intervalo de tempo...

		Imagem* img = mapImagens[estadoUnico];

		sf::Vector2f tamCorpo = corpo->getSize();
		sf::Vector2f escala = img->getEscala();

		img->atualizarFrameProjetil(indoParaEsq, dt);


		corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
		corpo->setTexture(img->getTextura());
		corpo->setScale(escala.x, escala.y);
	}

	void Animacao::addAnimacao(const char* caminhoTextura, std::string nomeAnimacao, const int qtdImg, const float frame_duration, const sf::Vector2f scale)
	{
		Imagem* img = new Imagem(caminhoTextura, qtdImg, frame_duration, scale);
		mapImagens.insert({ nomeAnimacao, img });
	}


}
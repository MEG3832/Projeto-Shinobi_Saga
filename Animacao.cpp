#include "Animacao.h"


Animacao::Animacao(sf::RectangleShape* body):
	corpo(body),
	mapImagens(),
	clock(),
	estadoAtual("")
{


}

Animacao::~Animacao() { }


void Animacao::atualizar(const bool indoParaEsq, std::string estadoImg)
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

	img->atualizar(indoParaEsq, dt);

	
	corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
	corpo->setTexture(img->getTextura());
	corpo->setScale(escala.x, escala.y);

}

void Animacao::addAnimacao(const char* caminhoTextura, std::string nomeAnimacao, const int qtdImg, const float frame_duration, const sf::Vector2f scale)
{
	Imagem* img = new Imagem(caminhoTextura, qtdImg, frame_duration, scale);
	mapImagens.insert({ nomeAnimacao, img });
}
#include "Animacao.h"

namespace Animadores {

	Animacao::Animacao(sf::RectangleShape* body) :
		corpo(body),
		mapImagens(),
		clock(),
		dt(0.0),
		estadoAtual("")
	{
	}

	Animacao::~Animacao() {}

	//atualizar de inimigo e de projetil

	void Animacao::atualizarAnimJog(const bool caindo, const bool subindo, const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg)
	{
		if (corpo) {
			if (estadoAtual != estadoImg) //caso o personagem esteja em um estado diferente do atual, resetamos o tempo e o "index" da textura
			{
				estadoAtual = estadoImg;
				mapImagens[estadoAtual]->resetar();
			}

			dt = clock.getElapsedTime().asSeconds();
			clock.restart(); //reinicia o relógio para guardar o intervalo de tempo...

			Imagem* img = mapImagens[estadoAtual];

			sf::Vector2f tamCorpo = corpo->getSize();
			sf::Vector2f escala = img->getEscala();

			img->atualizarFrameJog(caindo, subindo, indoParaEsq, rodaUmaVez, dt);


			corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
			corpo->setTexture(img->getTextura());
			corpo->setScale(escala.x, escala.y);
		}
		else {
			std::cout << "ERRO: nao eh possivel atualizar a animacao do jogador pois o corpo eh NULL" << std::endl;
		}
	}

	void Animacao::atualizarAnimInim(const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg)
	{
		if(corpo) {
			if (estadoAtual != estadoImg) //caso o personagem esteja em um estado diferente do atual, resetamos o tempo e o "index" da textura
			{
				estadoAtual = estadoImg;
				mapImagens[estadoAtual]->resetar();
			}

			dt = clock.getElapsedTime().asSeconds();
			clock.restart(); //reinicia o relógio para guardar o intervalo de tempo...

			Imagem* img = mapImagens[estadoAtual];

			sf::Vector2f tamCorpo = corpo->getSize();
			sf::Vector2f escala = img->getEscala();

			img->atualizarFrameInim(indoParaEsq, rodaUmaVez, dt);


			corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
			corpo->setTexture(img->getTextura());
			corpo->setScale(escala.x, escala.y);
		}
		else {
			std::cout << "ERRO: nao eh possivel atualizar a animacao do inimigo pois o corpo eh NULL" << std::endl;
		}

	}

	void Animacao::atualizarAnimProjetil(const bool indoParaEsq, std::string estadoUnico)
	{
		if(corpo) {
			if (estadoAtual != estadoUnico) //caso o personagem esteja em um estado diferente do atual, resetamos o tempo e o "index" da textura
			{
				estadoAtual = estadoUnico;
				mapImagens[estadoAtual]->resetar();
			}

			dt = clock.getElapsedTime().asSeconds();
			clock.restart(); //reinicia o relógio para guardar o intervalo de tempo...

			Imagem* img = mapImagens[estadoUnico];

			sf::Vector2f tamCorpo = corpo->getSize();
			sf::Vector2f escala = img->getEscala();

			img->atualizarFrameProjetil(indoParaEsq, dt);

			if (img->getImgAtual() == 4)
				img->resetar(); //para o projétil, não usarmos o resto das imagens da sprite, então resetamos...

			corpo->setTextureRect(img->getRetang()); //usando o intRect aqui! 
			corpo->setTexture(img->getTextura());
			corpo->setScale(escala.x, escala.y);
		}
		else {
			std::cout << "ERRO: nao eh possivel atualizar a animacao do projetil pois o corpo eh NULL" << std::endl;
		}
	}

	void Animacao::addAnimacao(const char* caminhoTextura, std::string nomeAnimacao, const int qtdImg, const float frame_duration, const sf::Vector2f scale)
	{
		Imagem* img = new Imagem(caminhoTextura, qtdImg, frame_duration, scale);
		mapImagens.insert({ nomeAnimacao, img });
	}

	const int Animacao::getImgAtual() {
		if (mapImagens[estadoAtual]) {
			return mapImagens[estadoAtual]->getImgAtual();
		}
		else {
			std::cerr << "ERRO: nao eh possivel retornar a imagem atual pois a imagem eh NULL" << std::endl;
			return -1;
		}
	}

	const float Animacao::getTempoTotal() {
		if (mapImagens[estadoAtual]) {
			return mapImagens[estadoAtual]->getTempoTotal();
		}
		else {
			std::cerr << "ERRO: nao eh possivel retornar o tempo total pois a imagem eh NULL" << std::endl;
			return -1.0;
		}
	}

	const std::string Animacao::getEstadoAtual() {
		return estadoAtual;
	}

	void Animacao::setImgAtual(int ia) {
		mapImagens[estadoAtual]->setImgAtual(ia);
	}

	void Animacao::setTempoTotal(float tt) {
		mapImagens[estadoAtual]->setTempoTotal(tt);
	}

	void Animacao::setEstadoAtual(std::string ea) {
		estadoAtual = ea;
	}
}
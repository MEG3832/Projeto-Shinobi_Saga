#include "Camada.h"

Camada::Camada(sf::Vector2f tamJanela, sf::Texture textura, const float vel) :
	tamJanela(tamJanela),
	textura(textura),
	dimensao(0,0,0,0),
	vel(vel)
{
	// Delimita o tamanho da textura
	dimensao.width = -std::abs(static_cast<float>(textura.getSize().x));
	dimensao.height = static_cast<float>(textura.getSize().y);
	dimensao.left = static_cast<float>(textura.getSize().x);

	// Dá o tamanho do fundo, sua posição inicial e seta a sua textura
	fundo.setSize(tamJanela);
	fundo.setTexture(&this->textura);
	fundo.setPosition(5.0f, 0.0f);

	fundoAuxiliar.setSize(tamJanela);
	fundoAuxiliar.setTexture(&this->textura);
	fundoAuxiliar.setPosition(tamJanela.x, 0.0f);
}

Camada::~Camada()
{}

// A textura principal vira a auxiliar e vice-versa
void Camada::trocarTextura() {
	sf::RectangleShape temp = fundo;
	fundo = fundoAuxiliar;
	fundoAuxiliar = temp;
}

void Camada::desenharCamada(sf::RenderWindow* window) {
	if (window) {
		window->draw(fundo);
		if (vel) {
			window->draw(fundoAuxiliar);
		}
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
	}
}

// Atualiza a posição dos fundo de acordo com o movimento realizado
void Camada::atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual) {
	sf::Vector2f posFundo = fundo.getPosition();
	sf::Vector2f posFundoAux = fundoAuxiliar.getPosition();
	const float dx = ds.x * 0.5f;	// Suaviliza o movimento em x
	const float posDireita = posCameraAtual.x + tamJanela.x / 2.0f;
	const float posEsquerda = posCameraAtual.x - tamJanela.x / 2.0f;

	if (vel) {	// Se está se movendo
		// Movimenta os fundos em um dx
		fundo.move(dx * -vel, 0.0f);
		fundoAuxiliar.move(dx * -vel, 0.0f);


		if (ds.x > 0.0f) {	// Câmera está se movendo para a direita
			if (posFundo.x + tamJanela.x < posEsquerda) {	// Se o fundo principal foi para trás da borda esquerda, troca com o fundo auxiliar
				trocarTextura();
				fundo.setPosition(posEsquerda, 0.0f);
				fundoAuxiliar.setPosition(posDireita, 0.0f);
			}
		}
		// trocar depois para uma comparação com a borda direita
		else {
			if (posFundo.x > posEsquerda) {	// O fundo começou a ultrapassar a borda direita
				trocarTextura();
				fundo.setPosition(posEsquerda - tamJanela.x, 0.0f);
				fundoAuxiliar.setPosition(posEsquerda, 0.0f);
			}
		}
	}
	else {	// Se está parado
		fundo.setPosition(posEsquerda, 0.0f);
	}
}
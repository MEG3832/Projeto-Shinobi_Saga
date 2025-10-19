#include "Camada.h"

Camada::Camada(sf::Vector2f tamJanela, sf::Texture testura, const float vel) :
	tamJanela(tamJanela), textura(textura), dimensao(0,0,0,0), vel(vel)
{
	// Delimita o tamanho da textura
	dimensao.width = -std::abs(static_cast<float>(textura.getSize().x));
	dimensao.height = static_cast<float>(textura.getSize().y);
	dimensao.left = static_cast<float>(textura.getSize().x);

	// Dá o tamanho do fundo, sua posição inicial e setta a sua textura
	fundo.setSize(tamJanela);
	fundo.setTexture(&this->textura);
	fundo.setPosition(0.0f, 0.0f);

	fundoAuxiliar.setSize(tamJanela);
	fundoAuxiliar.setTexture(&this->textura);
	fundo.setPosition(tamJanela.x, 0.0f);
}

Camada::~Camada() 
{}

// A textura principal vira a auxiliar e vice-versa
void Camada::trocarTextura() {
	sf::RectangleShape t = fundoAuxiliar;		
	fundoAuxiliar = fundo;
	fundo = t;
}

void Camada::desenharCamada(sf::RenderWindow* window) {
	window->draw(fundo);
	if (vel) {
		window->draw(fundoAuxiliar);
	}
}

// Atualiza a posição dos fundo de acordo com o movimento realizado
void Camada::atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual) {
	const float posDireita = posCameraAtual.x + tamJanela.x / 2.0f;
	const float posEsquerda = posCameraAtual.x - tamJanela.x / 2.0f;
	
	if (vel){	// Se está se movendo
		// Movimenta os fundos em um dx
		fundo.move(ds.x * -vel, 0.0f);
		fundoAuxiliar.move(ds.x * -vel, 0.0f);

		if (ds.x > 0.0f) {	// Câmera está se movendo para a esquerda
			if (fundo.getPosition().x + tamJanela.x < posEsquerda) {	// Se o fundo principal foi para trás da borda esquerda, troca com o fundo auxiliar
				trocarTextura();
				fundo.setPosition(posEsquerda, 0.0f);
				fundoAuxiliar.setPosition(posDireita, 0.0f);
			}
		}
		// trocar depois para uma comparação com a borda direita
		else {
			if (fundo.getPosition().x  > posEsquerda) {	// O fundo começou a ultrapassar a borda direita
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
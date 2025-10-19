#pragma once
#include "Header.h"
#include "Coord.h"

class Camada
{
	private:
		const sf::Vector2f tamJanela;
		sf::IntRect dimensao;
		const float vel;

		sf::Texture textura;
		sf::RectangleShape fundo;
		sf::RectangleShape fundoAuxiliar;

		void trocarTextura();

	public:
		Camada(sf::Vector2f tamJanela, sf::Texture textura, const float vel);
		Camada();
		~Camada();
		void desenharCamada(sf::RenderWindow* window);
		void atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual);
};


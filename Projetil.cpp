#include "Projetil.h"

namespace Entidades {

	Projetil::Projetil() :
		Entidade(),
		ativo(false)
	{
		corpo = new sf::RectangleShape(sf::Vector2f(30.0f, 45.0f));
		corpo->setPosition(sf::Vector2f(150, 500));	// Posição qualquer para teste
		corpo->setFillColor(sf::Color::Yellow);	// Pintando de vermelho só pra ficar visivel
	}

	Projetil::~Projetil() {
		ativo = false;
	}

	void Projetil::executar() {
		return;
	}

	void Projetil::salvar() {
		return;
	}

	void Projetil::inicializaAnimacoes() {
		return;
	}

}
#include "Projetil.h"
#include "Jogador.h"

namespace Entidades {

	Projetil::Projetil() :
		Entidade(),
		ativo(false)
	{
		corpo = new sf::RectangleShape(sf::Vector2f(30.0f, 45.0f));
		corpo->setPosition(sf::Vector2f(150, 500));	// Posição qualquer para teste
		corpo->setFillColor(sf::Color::Yellow);	// Pintando de vermelho só pra ficar visivel

		veloc = sf::Vector2f(10.0f, 10.0f); //testar qual valor deixar!!

	}

	Projetil::~Projetil() {
		ativo = false;
	}

	void Projetil::setEstadoProj(bool estado)
	{
		ativo = estado;
		
	}

	void Projetil::setVelocidade(sf::Vector2f vel) {
		veloc = vel;
	}

	bool Projetil::getEstadoProj()
	{
		return ativo;
	}

	void Projetil::danificar(Personagens::Jogador* pJ)
	{
		if (pJ && ativo) {
			int dano_projetil = 20;
			pJ->diminuiVida(dano_projetil);

			std::cout << "Projetil acertou! Vida Jogador: " << pJ->getVida() << std::endl;

			// desativa o projétil ao colidir
			setEstadoProj(false);
		}
	}

	void Projetil::executar() {
		return;
	}

	void Projetil::salvar() {
		return;
	}

}
#include "Projetil.h"
#include "Kitsune.h"
//#include "Jogador.h"

namespace Entidades {

	Projetil::Projetil(Personagens::Kitsune* pKits) :
		Entidade(),
		pKitsune(pKits),
		ativo(false)
	{
		corpo = new sf::RectangleShape(sf::Vector2f(30.0f, 45.0f));
		corpo->setPosition(pKitsune->getPos());	// seta a posicao do projetil igual a posicao da kitsune....
		//corpo->setFillColor(sf::Color::Yellow);	// Pintando de vermelho só pra ficar visivel

		hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 75, corpo->getSize().y));
		hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
			corpo->getPosition().y);


		setAnimador(corpo);
		inicializaAnimacoes();

	}

	Projetil::~Projetil() {
		ativo = false;
	}

	void Projetil::setEstadoProj(bool estado)
	{
		ativo = estado;
		
	}

	bool Projetil::getEstadoProj()
	{
		return ativo;
	}


	void Projetil::setVelocidade(sf::Vector2f vel) {
		veloc = vel;
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

		//verifica o estado do projétil.

		if (ativo)
		{ 
			if (veloc.x < 0) // se a velocidade de x dele é negativa, então é porque ele foi ativado para a esquerda
			{
				animador->atualizarAnimProjetil(true, "Fogo");
			}

			else
				animador->atualizarAnimProjetil(false, "Fogo");

			if (animador->getImgAtual("Fogo") == 4) //toca animacao antes de fazer ele se mover...
			{
				corpo->move(veloc);
				hitBox->setPosition(corpo->getPosition());

				float pos_x = corpo->getPosition().x;
				if (pos_x < 0.0f || pos_x > pGG->getWindow()->getSize().x)
				{
					setEstadoProj(false);
				}

				//a "desativação" do projétil quando atinge o jogador já eh tratada na colisão (dê uma olhada em danificar, o método anterior!)
			}

		}

		else
		{
			corpo->setPosition(pKitsune->getPos());
			hitBox->setPosition(pKitsune->getPos());
		}


	}

	void Projetil::salvar() {
		return;
	}

	void Projetil::inicializaAnimacoes()
	{
		//a animação do projétil só vai rodar uma vez.

		animador->addAnimacao("Imagens/Projetil_Fogo/Fire_2.png", "Fogo", 11, 0.1f, sf::Vector2f(1.0, 1.0));
	}

}
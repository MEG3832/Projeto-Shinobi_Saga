#include "Jogador.h"

Jogador::Jogador(int ident):
	Personagem()
{
	//pontos = 0;
	//id = ident;
	//veloc.x = 0.1;
	//veloc.y = 0.1;

	inicializaAnimacoes();

}

Jogador::Jogador():
	Personagem()
{
	//pontos = 0;
	//id = 1;
	//veloc.x = 0.1;
	//veloc.y = 0.1;

	inicializaAnimacoes();

}


Jogador::~Jogador()
{

}

void Jogador::executar()
{

}

void Jogador::salvar()
{

}

void Jogador::mover()
{
	if (id == 1) //jogador 1
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			pFig->move(veloc.x, 0.0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			pFig->move(0.0, -veloc.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			pFig->move(0.0, veloc.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			pFig->move(-veloc.x, 0.0);
		}

	}

	else //jogador 2
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			pFig->move(veloc.x, 0.0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			pFig->move(0.0, -veloc.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			pFig->move(0.0, veloc.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			pFig->move(-veloc.x, 0.0);
		}

	}
}


void Jogador::inicializaAnimacoes()
{

	animador->addAnimacao("Imagens/Idle.png", "parado", 6, 0.20, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Walk.png", "andando", 9, 0.12, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Run.png", "correndo", 8, 0.1, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Attack_1.png", "Ataque1", 4, 0.16, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Attack_2.png", "Ataque2", 5, 0.12, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Hurt.png", "Ferido", 3, 0.17, sf::Vector2f(6.0, 2.0));
}

void Jogador::atualizaAnimacao()
{

	bool paraEsq = false;

	animador->atualizar(paraEsq, "andando");
}



// atributos estáticos:


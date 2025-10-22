#include "Jogador.h"

Jogador::Jogador(int ident)
{
	pontos = 0;
	id = ident;
	veloc.x = 0.1;
	veloc.y = 0.1;
}

Jogador::Jogador()
{
	pontos = 0;
	id = 1;
	veloc.x = 0.1;
	veloc.y = 0.1;
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

// atributos estáticos:


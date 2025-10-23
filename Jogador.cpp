#include "Jogador.h"

Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam, int ident) :
	Personagem(),
	veloc(0.05, 0.05),
	pontos(0),
	id(ident)
{
	corpo = new sf::RectangleShape(tam);
}

Jogador::Jogador() :
	Personagem(),
	veloc(0.05, 0.05),
	pontos(0),
	id(1)
{
	corpo = new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
}


Jogador::~Jogador()
{
	veloc.x = 0;
	veloc.y = 0;
	pontos = -1;
	id = 0;
}

const sf::RectangleShape* Jogador::getCorpo() {
	return corpo;
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
			corpo->move(veloc.x, 0.0);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			corpo->move(0.0, -veloc.y);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			corpo->move(0.0, veloc.y);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			corpo->move(-veloc.x, 0.0);
		}

	}

	else //jogador 2
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			corpo->move(veloc.x, 0.0);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			corpo->move(0.0, -veloc.y);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			corpo->move(0.0, veloc.y);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			corpo->move(-veloc.x, 0.0);
		}

	}
}

// atributos estáticos:


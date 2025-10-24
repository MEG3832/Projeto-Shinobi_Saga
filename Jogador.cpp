#include "Jogador.h"

Jogador::Jogador():
	Personagem()
{
	//pontos = 0;
	//id = 1;
	//veloc.x = 0.1;
	//veloc.y = 0.1;

	inicializaAtributos();
	inicializaAnimacoes();

}


Jogador::~Jogador()
{

}

/*void Jogador::executar()
{

}*/

/*void Jogador::salvar()
{

}*/

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


void Jogador::inicializaAtributos()
{
	id = 0;
	num_vidas = 3;
	//dano= ?
}


void Jogador::inicializaAnimacoes()
{
	//Animações em loop

	animador->addAnimacao("Imagens/Samurai/Idle.png", "Parado", 6, 0.20, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Walk.png", "Andando", 9, 0.12, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Run.png", "Correndo", 8, 0.1, sf::Vector2f(6.0, 2.0));

	//Animações de pulo

	animador->addAnimacao("Imagens/Samurai/Jump.png", "Subindo", 9, 0.2, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Jump.png", "Descendo", 9, 0.2, sf::Vector2f(6.0, 2.0));

	//Animações que só devem rodar uma vez

	animador->addAnimacao("Imagens/Samurai/Attack_1.png", "Ataque1", 4, 0.16, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Attack_2.png", "Ataque2", 5, 0.12, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Attack_3.png", "Ataque3", 4, 0.18, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Dead.png", "Derrotado", 6, 0.45, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Hurt.png", "Ferido", 3, 0.17, sf::Vector2f(6.0, 2.0));
	animador->addAnimacao("Imagens/Samurai/Protection.png", "Protegendo", 2, 0.17, sf::Vector2f(6.0, 2.0));
}

void Jogador::atualizaAnimacao()
{

	bool rodaUmaVez = true;


	//terminar: fazer uma animação de cada estado de acordo com o valor de caindo, subindo, velocidade, se está no chão ou não...
	//vamos fazer as partes dos botões dentro de Jogador mesmo?

	//botão -> move o corpo e muda a animação 


	//teste:
	animador->atualizar(caindo, subindo, paraEsq, rodaUmaVez, "Ferido"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
}



// atributos estáticos:


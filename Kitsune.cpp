#include "Kitsune.h"

namespace Entidades
{
	namespace Personagens
	{
		Kitsune::Kitsune(Jogador* pJ) :
			Inimigo(pJ),
			pProjetil(nullptr)
		{
			raio_ativacao = 50.0f;
			tempo_cooldown = 5.0f;
			nivel_maldade = 1; // nível de maldade base
			paraEsq = true;
			veloc = sf::Vector2f(0.03f, 0.05f);
			tempoAndar = 4.0f;

			num_vidas = 250;

			cooldownAtordoado = 1.0f;

			corpo = new sf::RectangleShape(sf::Vector2f(140.0f, 150.0f));
			//corpo->setPosition(pos); //posicao??

			corpo->setPosition(300.0f, ALTURA_TELA - 50 - corpo->getSize().y);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 75, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);

			setAnimador(corpo);
			inicializaAnimacoes();

			pProjetil->setAnimador(pProjetil->getCorpo());
		}

		Kitsune::~Kitsune()
		{
			pProjetil = nullptr;
		}

		void Kitsune::mover()
		{
			Inimigo::perambular(); //posso fazer isso, né?
		}

		void Kitsune::criaProjetil()
		{
			Projetil* pProj = new Entidades::Projetil();



		}

		void Kitsune::inicializaAnimacoes()
		{
			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Kitsune/Idle.png", "Parado", 5, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Walk.png", "Andando", 9, 0.20f, sf::Vector2f(1.0, 1.0));


				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Kitsune/Attack_3.png", "Ataque3", 7, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Dead.png", "Derrotado", 10, 0.45f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Hurt.png", "Ferido", 2, 0.17f, sf::Vector2f(1.0, 1.0));

			}
			else
				std::cout << "ponteiro de animacao nulo!" << std::endl;
		}

		void Kitsune::inicializaAnimProjetil()
		{
			//if(pProjetil->)
		}
	}
}
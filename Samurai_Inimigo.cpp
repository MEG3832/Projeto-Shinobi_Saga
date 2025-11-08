#include "Samurai_Inimigo.h"
#include "Jogador.h"

namespace Entidades {
	namespace Personagens {

		Samurai_Inimigo::Samurai_Inimigo(Jogador* pJ, sf::Vector2f pos, sf::Vector2f tam) :
			Inimigo(pJ)
		{

			tamanho = tam.x;
			nivel_maldade = 1; // nível de maldade base
			paraEsq = true;
			veloc = sf::Vector2f(0.03f, 0.05f);
			tempoAndar = 4.0f;


			corpo = new sf::RectangleShape(tam);
			corpo->setPosition(pos);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x-75, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Samurai_Inimigo::~Samurai_Inimigo() {}

		void Samurai_Inimigo::executar()
		{
			mover();
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);
		}

		// 1. Comportamento de movimento (só perambula)
		void Samurai_Inimigo::mover()
		{
			Inimigo::perambular(); // Só chama a lógica base de andar
		}

		// 2. Quando o Samurai ATACA (colide com o jogador)
		void Samurai_Inimigo::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				int dano_calculado = nivel_maldade * (int)tamanho; // dano = nivel * tamanho

				pJ->diminuiVida(dano_calculado);
				std::cout << "Samurai causou " << dano_calculado << " de dano! Vida do Jogador: " << pJ->getVida() << std::endl;

				empurrar(pJ); // Chama o empurrão CUSTOMIZADO do Samurai
			}
			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}

		void Samurai_Inimigo::empurrar(Jogador* pJ)
		{
			sf::Vector2f velKnockBack;

			float tamanho = this->getTam().x;
			float força_empurrao = 1.0f + (tamanho / 75.0f); // Ex: Base 1.0 + força bônus pelo tamanho

			if (pJ) {
				sf::Vector2f centroJog = pJ->getPos() + (pJ->getTam()) / 2.0f;
				sf::Vector2f centroInim = this->getPos() + (this->getTam()) / 2.0f;
				sf::Vector2f vetor = centroJog - centroInim;

				float modulo = std::sqrt(vetor.x * vetor.x + vetor.y * vetor.y);

				if (modulo != 0)
					vetor = vetor / modulo;

				vetor *= força_empurrao;
				pJ->setVelKnockBack(vetor);
			}
			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;
		}


		void Samurai_Inimigo::inicializaAnimacoes()
		{
			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Samurai_Inimigo/Idle.png", "Parado", 5, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Walk.png", "Andando", 9, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.0, 1.0));



				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Samurai_Inimigo/Attack_1.png", "Ataque1", 4, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Attack_2.png", "Ataque2", 5, 0.12f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Attack_3.png", "Ataque3", 4, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Hurt.png", "Ferido", 2, 0.17f, sf::Vector2f(1.0, 1.0));

			}
			else
				std::cout << "ponteiro de animacao nulo!" << std::endl;
		}

	}
}
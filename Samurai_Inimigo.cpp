#include "Samurai_Inimigo.h"
#include "Jogador.h"

namespace Entidades {
	namespace Personagens {

		Samurai_Inimigo::Samurai_Inimigo(Jogador* pJ, float resist) :
			Inimigo(pJ)
		{
			resistencia = resist;
			nivel_maldade = 1; // nível de maldade base
			paraEsq = true;
			veloc = sf::Vector2f(0.03f, 0.05f);
			tempoAndar = 4.0f;

			// 2 frames * 0.17s/frame = 0.34s
			cooldownAtordoado = 0.34f;

			corpo = new sf::RectangleShape(sf::Vector2f(140.0f, 150.0f));
			//corpo->setPosition(pos); //posicao??

			corpo->setPosition(300.0f, ALTURA_TELA - 50 - corpo->getSize().y);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x-75, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
				corpo->getPosition().y);

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Samurai_Inimigo::~Samurai_Inimigo() {}

		void Samurai_Inimigo::executar()
		{
			Inimigo::executar(); //será que posso só fazer isso?
		}

		void Samurai_Inimigo::mover()
		{
			Inimigo::perambular(); //ele só perambula!
		}

		void Samurai_Inimigo::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				int dano_calculado = nivel_maldade * 15; //dano base

				pJ->diminuiVida(dano_calculado);
				std::cout << "Samurai causou " << dano_calculado << " de dano! Vida do Jogador: " << pJ->getVida() << std::endl;

				empurrar(pJ);
			}
			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}

		void Samurai_Inimigo::diminuiVida(int dano)
		{
			// 1. Checa se já está atordoado (lógica da base)
			if (atordoado || estaMorto) {
				return;
			}

			int dano_reduzido = 0;
			if (resistencia > 0.0f) {
				dano_reduzido = dano / resistencia;
			}
			else {
				dano_reduzido = dano; //para evitar divisão por zero
			}

			std::cout << "Samurai tomou " << dano_reduzido << " de dano (original: " << dano << ")" << std::endl;

			// Chama a implementação da classe base (provavelmente Personagem)
			// para aplicar o dano já reduzido.
			Personagem::diminuiVida(dano_reduzido);
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
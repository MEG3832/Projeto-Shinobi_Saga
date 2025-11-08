#include "Inimigo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Personagens {

		Inimigo::Inimigo(Jogador* pJ) :
			Personagem(),
			nivel_maldade(1),
			veloc(0.05f,0.05f),
			jogAlvo(pJ),
			paraEsq(true),
			cooldownAtaque(3.0f),
			relogioAtaque(),
			andando(false),
			relogioAndar(),
			tempoAndar(3.0),
			atordoado(false),
			cooldownAtordoado(0.5f), // Valor padrão
			estaMorto(false),
			intransponivel(true) // inimigos são "sólidos" por padrão
		{

			//corpo é feito nas classes folha
			
		}

		Inimigo::~Inimigo() {

			nivel_maldade = -1;
			veloc = sf::Vector2f(0.0f, 0.0f);
			jogAlvo = nullptr;
			cooldownAtaque = 0.0;
			andando = false;
			tempoAndar = 0;
		}

		void Inimigo::salvarDataBuffer() {
			return;
		}

		void Inimigo::executar() {

			//analisamos o estado do inimigo.
			
			if (estaMorto) {
				animador->atualizarAnimInim(paraEsq, true, "Derrotado");
				return;
			}

			if (atordoado) {
				if (relogioAtordoado.getElapsedTime().asSeconds() >= cooldownAtordoado) {
					atordoado = false;
				}
				else {
					animador->atualizarAnimInim(paraEsq, true, "Ferido");
				}
			}

			if (!atordoado) {

				mover();
			}


			if (hitBox && corpo) {
				hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
					corpo->getPosition().y);
			}
			
		}

		void Inimigo::diminuiVida(int dano)
		{
			// Não pode tomar dano se já estiver atordoado ou morto
			if (atordoado || estaMorto) {
				return;
			}

			// Não faz nada se o dano for 0 ou negativo
			if (dano <= 0) {
				return;
			}

			Personagem::diminuiVida(dano); // aplica o dano (da classe Personagem)

			// verifica o resultado do ataque
			if (getVida() <= 0) {
				estaMorto = true;
				atordoado = false; // Morte é mais importante que atordoamento
				setIntransponivel(false); // Inimigo morto pode ser atravessado
				std::cout << "Inimigo morreu!" << std::endl;
			}
			else {
				// Se tomou dano mas não morreu, fica atordoado
				atordoado = true;
				relogioAtordoado.restart();
				std::cout << "Inimigo tomou " << dano << " de dano. Vida: " << getVida() << std::endl;
			}
		}


		void Inimigo::danificar(Jogador* pJ) { //é reimplementado nas folhas

			if (pJ)
			{
				pJ->diminuiVida(nivel_maldade);
				std::cout << pJ->getVida() << std::endl;
				empurrar(pJ);
			}

			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}

		}

		void Inimigo::empurrar(Jogador* pJ) //empurrão base
		{
			//nesse método, vamos calcular a direção do vetor KnockBack que queremos passar para o jogador,
			// e, depois disso, iremos multiplicar por uma "força" (intensidade)

			sf::Vector2f velKnockBack;
			float força_empurrao = 1.5f;

			if (pJ) {

				//calcula os centros do inimigo e do jogador

				sf::Vector2f centroJog = pJ->getPos() + (pJ->getTam()) / 2.0f;
				sf::Vector2f centroInim = this->getPos() + (this->getTam()) / 2.0f;

				sf::Vector2f vetor = centroJog - centroInim; //nessa ordem!

				//normalizamos o vetor... e para isso, calculamos seu módulo

				float modulo = std::sqrt(vetor.x * vetor.x + vetor.y * vetor.y);

				if(modulo!=0)
					vetor = vetor / modulo; //agora o vetor é um vetor normalizado!

				vetor *= força_empurrao;

				pJ->setVelKnockBack(vetor);

			}

			else
				std::cout << "ponteiro de jogador nulo!" << std::endl;

		}

		void Inimigo::perambular()
		{
			if (relogioAndar.getElapsedTime().asSeconds() >= tempoAndar)
			{
				relogioAndar.restart();
				andando = !andando;
				paraEsq = (rand() % 2 == 0);
			}

			if (andando)
			{
				if (paraEsq)
					corpo->move(-veloc.x, 0.0f);
				else
					corpo->move(veloc.x, 0.0f);

				animador->atualizarAnimInim(paraEsq, false, "Andando");
			}
			else
			{
				corpo->move(0.0f, 0.0f);
				animador->atualizarAnimInim(paraEsq, false, "Parado");
			}
		}


		void Inimigo::salvar() {
			return;
		}

		void Inimigo::mover() {
			return;
		}

		void Inimigo::inicializaAnimacoes() {
			return;
		}

	}

}
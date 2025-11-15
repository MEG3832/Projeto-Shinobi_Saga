#include "Inimigo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Personagens {

		Inimigo::Inimigo(Jogador* pJ) :
			Personagem(),
			nivel_maldade(1),
			jogAlvo(pJ),
			cooldownAtaque(3.0f),
			relogioAtaque(),
			relogioAndar(),
			tempoAndar(3.0),
			cooldownAtordoado(0.5f), // Valor padrão
			estado_atual(PARADO)
		{
			//corpo é feito nas classes folha
			veloc.x = 0.05f;
			veloc.y = 0.0f;
		}

		Inimigo::~Inimigo() {

			nivel_maldade = -1;
			veloc = sf::Vector2f(0.0f, 0.0f);
			jogAlvo = nullptr;
			cooldownAtaque = 0.0;
			estado_atual = PARADO;
			tempoAndar = 0;
		}

		void Inimigo::salvarDataBuffer() {
			return;
		}

		void Inimigo::executar() {

			//analisamos o estado do inimigo.
			
			if (MORRENDO == estado_atual) {
				animador->atualizarAnimInim(paraEsq, true, "Derrotado");
				return;
			}

			if (FERIDO == estado_atual) {
				if (relogioAtordoado.getElapsedTime().asSeconds() >= cooldownAtordoado) {
					estado_atual = PARADO;
					relogioAndar.restart();
				}
				else {
					animador->atualizarAnimInim(paraEsq, true, "Ferido");
				}
			}

			if (FERIDO != estado_atual) {

				mover();
			}
		}

		void Inimigo::diminuiVida(int dano)
		{
			//não toma dano se já estiver atordoado ou morto
			if (FERIDO == estado_atual || MORRENDO == estado_atual) {
				return;
			}

			// não faz nada se o dano for 0 ou negativo
			if (dano <= 0) {
				return;
			}

			// Na verdade precisa adaptar para o caso em que quem estah atacando eh o outro jogador e nao o alvo
			if (jogAlvo) {
				if (corpo) {
					if (jogAlvo->getCorpo()->getPosition().x < corpo->getPosition().x) {
						paraEsq = true;
					}
					else
					{
						paraEsq = false;
					}
				}
				else {
					std::cerr << "ERRO: nao eh possivel virar o inimigo pois o corpo dele eh NULL" << std::endl;
				}
			}
			else {
				std::cerr << "ERRO: nao eh possivel virar o inimigo pois o jogador alvo eh NULL" << std::endl;
			}

			Personagem::diminuiVida(dano); // aplica o dano (da classe Personagem)

			// verifica o resultado do ataque
			if (getVida() <= 0) {
				estado_atual = MORRENDO;
				setIntransponivel(false); // Inimigo morto pode ser atravessado
				std::cout << "Inimigo morreu!" << std::endl;
			}
			else {
				// Se tomou dano mas não morreu, fica atordoado
				estado_atual = FERIDO;
				relogioAtordoado.restart();
				std::cout << "Inimigo tomou " << dano << " de dano. Vida: " << getVida() << std::endl;
			}
		}


		void Inimigo::danificar(Jogador* pJ) { //é reimplementado nas folhas

			if (pJ)
			{
				pJ->diminuiVida(nivel_maldade);
				std::cout << pJ->getVida() << std::endl;
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
			float força_empurrao = 8.0f;

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

				if (ANDANDO == estado_atual) {
					estado_atual = PARADO;
				}
				else {
					estado_atual = ANDANDO;
				}

				paraEsq = (rand() % 2 == 0);
			}

			if (ANDANDO == estado_atual)
			{
				if (paraEsq) {
					corpo->move(-veloc.x, 0.0f);
					hitBox->move(-veloc.x - 0.5f, 0.0f);
				}
				else {
					corpo->move(veloc.x, 0.0f);
					hitBox->move(veloc.x, 0.0f);
				}

				animador->atualizarAnimInim(paraEsq, false, "Andando");
			}
			else
			{
				animador->atualizarAnimInim(paraEsq, false, "Parado");
			}
		}

		void Inimigo::morrer() {
			estado_atual = MORRENDO;
		}

		bool Inimigo::getFerido() {
			if (FERIDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

		bool Inimigo::getMorto() {
			if (MORRENDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

	}

}
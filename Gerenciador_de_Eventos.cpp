#include "Gerenciador_de_Eventos.h"

namespace Gerenciadores {

	Gerenciador_de_Eventos* Gerenciador_de_Eventos::pEventos = nullptr;

	Gerenciador_de_Eventos::Gerenciador_de_Eventos() :
		pGrafico(pGrafico->getGerenciadorGrafico()),
		pJogador(new Entidades::Personagens::Jogador())
	{}

	Gerenciador_de_Eventos::~Gerenciador_de_Eventos() {
		pGrafico = nullptr;
		pJogador = nullptr;
	}

	Gerenciador_de_Eventos* Gerenciador_de_Eventos::getGerenciadorEventos() {
		if(!pEventos) {
			pEventos = new Gerenciador_de_Eventos();
		}

		return pEventos;
	}

	void Gerenciador_de_Eventos::setJogador(Entidades::Personagens::Jogador* pJogador) {
		this->pJogador = pJogador;
	}

	/* TECLAS:
	* Atacar - Q
	* Pular - W
	* Andar para a direita - D
	* Andar para a esquerda - E
	*/
	void Gerenciador_de_Eventos::verificaTeclaPressionada() {

		sf::Vector2f direcaoInput(0.0f, 0.0f); //resetamos a "direção" para zero (jogador parado) a cada iteração do loop do jogo
											   //para que a função mover funcione corretamente quanto ao knockback, msm qnd ele nn estiver se movendo

		if (!pJogador->getAtacando()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				pJogador->atacar();
			}
			else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
						pJogador->correr(true);
					}
					else {
						pJogador->correr(false);
					}

					direcaoInput.x += 1.0f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					direcaoInput.y -= 1.0f;
					pJogador->pular();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					direcaoInput.y += 1.0f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
						pJogador->correr(true);
					}
					else {
						pJogador->correr(false);
					}

					direcaoInput.x -= 1.0f;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pGrafico->fecharJanela();
		}
	
		pJogador->setDirecao(direcaoInput);
	}

	// Verifica qual tecla está sendo pressionada e muda a diração do jogador segundo ela
	void Gerenciador_de_Eventos::executar() {
		if(pGrafico) {
			sf::Event evento;
			while (pGrafico->getWindow()->pollEvent(evento)) {
				if (evento.type == sf::Event::Closed) {
					pGrafico->fecharJanela();
				}
			}
			verificaTeclaPressionada();
		}
		else {
			std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
		}
	}

}
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

	void Gerenciador_de_Eventos::verificaTeclaPressionada() {

		sf::Vector2f direcaoInput(0.0f, 0.0f); //resetamos a "direção" para zero (jogador parado) a cada iteração do loop do jogo
											   //para que a função mover funcione corretamente quanto ao knockback, msm qnd ele nn estiver se movendo

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direcaoInput.x += 1.0f;
			//pJogador->mover(); -> é chamado no loop do jogo!, por isso estou comentando...
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			direcaoInput.y -= 1.0f;
			//pJogador->mover();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			direcaoInput.y += 1.0f;
			//pJogador->mover();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			direcaoInput.x -= 1.0f;
			//pJogador->mover();
		}

		pJogador->setDirecao(direcaoInput);

	}

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
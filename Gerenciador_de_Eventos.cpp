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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			pJogador->setDirecao('D');
			//pJogador->mover(); -> é chamado no loop do jogo!, por isso estou comentando...
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			pJogador->setDirecao('C');
			//pJogador->mover();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			pJogador->setDirecao('B');
			//pJogador->mover();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			pJogador->setDirecao('E');
			//pJogador->mover();
		}
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
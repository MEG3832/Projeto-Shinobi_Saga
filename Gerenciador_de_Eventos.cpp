#include "Gerenciador_de_Eventos.h"
#include "Menu.h"
#include "Menu_Salvamento_Ranking.h"
#include "Jogo.h"

namespace Gerenciadores {

	Gerenciador_de_Eventos* Gerenciador_de_Eventos::pEventos = nullptr;

	Gerenciador_de_Eventos::Gerenciador_de_Eventos() :
		pGrafico(pGrafico->getGerenciadorGrafico()),
		pJogador(new Entidades::Personagens::Jogador()),
		pJogo(nullptr)
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
	* Defender - S
	* Pular - W
	* Andar para a direita - D
	* Andar para a esquerda - E
	* Sair - Esc
	* Pause - P
	*/

	void Gerenciador_de_Eventos::verificaTeclaPressionada() {

		sf::Vector2f direcaoInput(0.0f, 0.0f); //resetamos a "direção" para zero (jogador parado) a cada iteração do loop do jogo
											   //para que a função mover funcione corretamente quanto ao knockback, msm qnd ele nn estiver se movendo

		if (pJogador) {

			if (!pJogador->getAtacando() && !pJogador->getMorto() && !pJogador->getFerido()) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !pJogador->getSubindo() && !pJogador->protegendo()) {
						pJogador->correr(true);
					}
					else {
						pJogador->correr(false);
					}

					direcaoInput.x += 1.0f;
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !pJogador->getSubindo() && !pJogador->protegendo()) {
						pJogador->correr(true);
					}
					else {
						pJogador->correr(false);
					}

					direcaoInput.x -= 1.0f;
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					pJogador->atacar();
				}

				else if (!pJogador->getSubindo()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						direcaoInput.y -= 1.0f;
						pJogador->pular();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						pJogador->setDefesa(true);
					}
					else {
						pJogador->setDefesa(false);
					}
				}
			}
		}

		else {
			std::cerr << "ERRO: Nao eh possivel atualizar o moviemnto do jogador pois o ponteiro dele eh NULL" << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (pGrafico) {
				pGrafico->fecharJanela();
			}
			else {
				std::cerr << "ERRO: Nao eh possivel fechar a janela pois o Gerenciador Grafico eh NULL" << std::endl;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			if (pJogo) {
				pJogo->setEstado(1);	// No jogo, 1 indica o estado pause
			}
			else {
				std::cerr << "ERRO: Nao eh possivel pausar pois o Jogo eh NULL" << std::endl;
			}
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

	void Gerenciador_de_Eventos::executarMenu(Menu* pMenu) {
		if (pGrafico) {
			sf::Event evento;
			while (pGrafico->getWindow()->pollEvent(evento)) {
				if (evento.type == sf::Event::Closed) {
					pGrafico->fecharJanela();
				}
				else if (evento.type == sf::Event::KeyPressed) {
					verificaTeclaPressionadaMenu(pMenu, evento.key.code);
				}
			}
		}
		else {
			std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
		}
	}

	void Gerenciador_de_Eventos::executarMenuSave(Menu_Salvamento_Ranking* pMenu) {
		if (pGrafico) {
			sf::Event evento;
			while (pGrafico->getWindow()->pollEvent(evento)) {
				if (evento.type == sf::Event::Closed) {
					pGrafico->fecharJanela();
				}
				else if (evento.type == sf::Event::KeyPressed) {
					verificaTeclaPressionadaMenuSave(pMenu, evento.key.code);
				}
			}
		}
		else {
			std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
		}
	}

	void Gerenciador_de_Eventos::verificaTeclaPressionadaMenu(Menu* pMenu, sf::Keyboard::Key tecla) {
		if (pMenu) {

			if (sf::Keyboard::Down == tecla)
			{
				pMenu->operator++();
			}
			else if (sf::Keyboard::Up == tecla) {
				pMenu->operator--();
			}
			else if (sf::Keyboard::Enter == tecla) {
				pMenu->selecionar();
			}
		}
		else {
			std::cerr << "ERRO: Nao eh possivel mover a selecao pois o Menu eh NULL" << std::endl;
		}
	}

	void Gerenciador_de_Eventos::verificaTeclaPressionadaMenuSave(Menu_Salvamento_Ranking* pMenu, sf::Keyboard::Key tecla) {
		if (pMenu) {
			if (tecla >= 0 && tecla <= 25) {	// Baseia-se no event.kay.code e na tabela ASCII
				char c = tecla + 65;
				pMenu->addCaractere(c);
			}
			else if (sf::Keyboard::Space == tecla) {
				pMenu->addCaractere(' ');
			}
			else if (sf::Keyboard::BackSpace == tecla) {
				pMenu->removeCaractere();
			}

			else if (sf::Keyboard::Down == tecla)
			{
				pMenu->operator++();
			}
			else if (sf::Keyboard::Up == tecla) {
				pMenu->operator--();
			}
			else if (sf::Keyboard::Enter == tecla) {
				pMenu->selecionar();
			}
		}
		else {
			std::cerr << "ERRO: Nao eh possivel escrever o nome do jogador pois o Menu eh NULL" << std::endl;
		}
	}

	void Gerenciador_de_Eventos::setJogo(Jogo* pJ) {
		pJogo = pJ;
	}
}
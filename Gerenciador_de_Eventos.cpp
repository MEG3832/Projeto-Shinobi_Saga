#include "Gerenciador_de_Eventos.h"
#include "Menu.h"
#include "Menu_Salvamento_Ranking.h"
#include "Jogo.h"

namespace Gerenciadores {

	Gerenciador_de_Eventos* Gerenciador_de_Eventos::pEventos = nullptr;

	Gerenciador_de_Eventos::Gerenciador_de_Eventos() :
		pJogador1(nullptr),
		pJogador2(nullptr),
		pJogo(nullptr),
		pGrafico(pGrafico->getGerenciadorGrafico())
	{}

	Gerenciador_de_Eventos::~Gerenciador_de_Eventos() {
		pGrafico = nullptr;
		pJogador1 = nullptr;
		pJogador2 = nullptr;
		pJogo = nullptr;
	}

	Gerenciador_de_Eventos* Gerenciador_de_Eventos::getGerenciadorEventos() {
		if(!pEventos) {
			pEventos = new Gerenciador_de_Eventos();
		}

		return pEventos;
	}

	void Gerenciador_de_Eventos::setJogador1(Entidades::Personagens::Jogador* pJogador) {
		pJogador1 = pJogador;
	}

	void Gerenciador_de_Eventos::setJogador2(Entidades::Personagens::Jogador* pJogador) {
		pJogador2 = pJogador;
	}

	/* TECLAS (para o jogador 1):
	* Atacar - Q
	* Defender - S
	* Pular - W
	* Andar para a direita - D
	* Andar para a esquerda - E
	* Sair - Esc
	* Pause - P
	* Andar para a esquerda - A
	* Correr - Left Shift
	*/

	void Gerenciador_de_Eventos::verificaTeclaPressionada() {

		sf::Vector2f direcaoInput(0.0f, 0.0f); //resetamos a "direção" para zero (jogador parado) a cada iteração do loop do jogo
											   //para que a função mover funcione corretamente quanto ao knockback, msm qnd ele nn estiver se movendo

		//verificação de teclas para o Jogador 1:
		if (pJogador1) {

			if (!pJogador1->getAtacando() && !pJogador1->getMorto() && !pJogador1->getFerido()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !pJogador1->getSubindo() && !pJogador1->protegendo()) {
						pJogador1->correr(true);
					}
					else {
						pJogador1->correr(false);
					}

					direcaoInput.x += 1.0f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !pJogador1->getSubindo() && !pJogador1->protegendo()) {
						pJogador1->correr(true);
					}
					else {
						pJogador1->correr(false);
					}

					direcaoInput.x -= 1.0f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					pJogador1->atacar();
				}

				if (!pJogador1->getSubindo()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						direcaoInput.y -= 1.0f;
						pJogador1->pular();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						pJogador1->setDefesa(true);
					}
					else {
						pJogador1->setDefesa(false);
					}
				}
			}

			pJogador1->setDirecao(direcaoInput);

		}

		direcaoInput.x = 0.0f;
		direcaoInput.y = 0.0f;

		//--------------------------------//

		/* TECLAS (para o jogador 2):
		* Atacar - M
		* Defender - setinha p/baixo
		* Pular - setinha p/ cima
		* Andar para a direita - setinha p/ direita
		* Andar para a esquerda - setinha p/ esquerda
		* Correr - N
		*/


		//verificação de teclas para o Jogador 2:

		if (pJogador2) //primeiro vê se o jogador 2 existe...
		{

			if (!pJogador2->getAtacando() && !pJogador2->getMorto() && !pJogador2->getFerido()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !pJogador2->getSubindo() && !pJogador2->protegendo()) {
						pJogador2->correr(true);
					}
					else {
						pJogador2->correr(false);
					}

					direcaoInput.x += 1.0f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !pJogador2->getSubindo() && !pJogador2->protegendo()) {
						pJogador2->correr(true);
					}
					else {
						pJogador2->correr(false);
					}

					direcaoInput.x -= 1.0f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				{
					pJogador2->atacar();
				}

				if (!pJogador2->getSubindo()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						direcaoInput.y -= 1.0f;
						pJogador2->pular();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						pJogador2->setDefesa(true);
					}
					else {
						pJogador2->setDefesa(false);
					}
				}
			}

			pJogador2->setDirecao(direcaoInput);

		}
		
		if (pGrafico) {
			//apenas verifica se apertou o ESC:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				pGrafico->fecharJanela();
			}
		}

		if (pJogo) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				pJogo->setEstado(1);	// MENU_PAUSE
			}
		}

	}

	// Verifica qual tecla está sendo pressionada e muda a diração do jogador segundo ela
	void Gerenciador_de_Eventos::executar() {
		if(pGrafico) {
			if (pGrafico->getWindow()) {
				sf::Event evento;
				while (pGrafico->getWindow()->pollEvent(evento)) {
					if (evento.type == sf::Event::Closed) {
						pGrafico->fecharJanela();
					}
				}
				verificaTeclaPressionada();
			}
		}
		else {
			std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
		}
	}

	void Gerenciador_de_Eventos::executarMenu(Menu* pMenu) {
		if (pGrafico) {
			if (pGrafico->getWindow()) {
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
		}
		else {
			std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
		}
	}

	void Gerenciador_de_Eventos::executarMenuSave(Menu_Salvamento_Ranking* pMenu) {
		if (pGrafico) {
			if (pGrafico->getWindow()) {
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
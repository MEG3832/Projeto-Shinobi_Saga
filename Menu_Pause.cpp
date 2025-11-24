#include "Menu_Pause.h"
#include "Jogo.h"

Menu_Pause::Menu_Pause() :
	Menu(),
	pFase(nullptr)
{
	inicializaFundo();
	inicializaTexto();
}

Menu_Pause::~Menu_Pause()
{
	pFase = nullptr;
}

void Menu_Pause::executar() {
	selecionado = 0;
	parar = false;
	while (!parar) {
		if (pGG) {
			if (GE) {
				executa = false;
				pGG->limpaJanela();
				pGG->atualizaCamera(sf::Vector2f(pGG->getCamera().getCenter().x + 1, pGG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenu(static_cast<Menu*>(this));	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				desenharTexto();
				Menu::desenharTexto();
				pGG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (0 == selecionado) {
							pJog->voltarEstado();
							parar = true;
						}
						else if (1 == selecionado) {
							if (pFase) {
								pFase->salvar();
								Entidades::Entidade::limparBuffers();
							}
							else {
								std::cerr << "ERRO: Nao eh possivel salvar a fase pois seu ponteiro eh NULL" << std::endl;
							}

							parar = false;
						}
						else if (2 == selecionado) {
							pJog->setEstado(0);	// o corresponde ao menu principal no enum do jogo
							parar = true;
						}
						else if (3 == selecionado) {
							parar = true;
							exit(1);
						}
					}
					else {
						std::cerr << "ERRO: Nao eh possivel executar o comando pois o jogo eh NULL" << std::endl;
					}
				}

			}
			else {
				std::cerr << "ERRO: Nao eh possivel criar a tela pois o Gerenciador de Eventos eh NULL" << std::endl;
			}
		}
		else {
			std::cerr << "ERRO: Nao eh possivel imprimir na tela pois o Gerenciador Grafico eh NULL" << std::endl;
		}
	}
}

void Menu_Pause::inicializaTexto() {
	texto.clear();

	if (pGG) {
		sf::Text temp;

		temp.setCharacterSize(30);
		temp.setFillColor(sf::Color(sf::Color::White));
		temp.setOutlineColor(sf::Color::Black);
		temp.setOutlineThickness(3);
		temp.setFont(fonte);

		temp.setString("Voltar");
		temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 25);
		texto.push_back(temp);

		temp.setString("Salvar Jogo");
		temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 25 + 45);
		texto.push_back(temp);

		temp.setString("Menu Principal");
		temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 25 + 45 * 2);
		texto.push_back(temp);

		temp.setString("Sair");
		temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 25 + 45 * 3);
		texto.push_back(temp);
	}
}

void Menu_Pause::desenharTexto() {
	if (pGG) {
		titulo.setPosition(pGG->getCamera().getCenter().x - titulo.getLocalBounds().width / 2, titulo.getPosition().y);
		pGG->desenharTexto(titulo);
	}
	else {
		std::cerr << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
}

void Menu_Pause::setFase(Fases::Fase* pF) {
	pFase = pF;
}
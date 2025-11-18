#include "Menu.h"
#include "Jogo.h"
#include "Menu_Fase.h"

Menu::Menu() :
	Ente(),
	pJog(nullptr),
	GG(GG->getGerenciadorGrafico()),
	GE(GE->getGerenciadorEventos()),
	fundo(),
	fonte(),
	texto(),
	selecionado(1),
	executa(false),
	parar(false)
{
	inicializaFundo();
	inicializaTexto();
}

Menu::~Menu() {
	pJog = nullptr;
	GG = nullptr;
	GE = nullptr;
	selecionado = -1;
	executa = false;
}

void Menu::executar() {
	parar = false;
	while (!parar) {
		if (GG) {
			if (GE) {
				executa = false;
				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 1, GG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenu(this);	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				desenharTexto();
				GG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (1 == selecionado) {
							pJog->setEstadoMenuFases();
							parar = true;
						}
						if (2 == selecionado) {
							pJog->carregar();
							parar = true;
						}
						if (3 == selecionado) {
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

void Menu::inicializaFundo() {
	// As velocidades dão o efeito parallax
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada1.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada2.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.00000000001f, "Imagens/JapanVillage/Camada3.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000000001f, "Imagens/JapanVillage/Camada4.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000000001f, "Imagens/JapanVillage/Camada5.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.05f, "Imagens/JapanVillage/Camada6.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada7.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.15f, "Imagens/JapanVillage/Camada8.png");
	fundo.addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.05f, "Imagens/JapanVillage/Camada9.png");
}

void Menu::inicializaTexto() {
	texto.clear();
	fonte.loadFromFile("Fonte/superstar_memesbruh03.ttf");

	sf::Text temp;
	temp.setString("NOME DO JOGO");
	temp.setCharacterSize(85);
	temp.setFillColor(sf::Color(sf::Color::White));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 150);
	temp.setFont(fonte);
	texto.push_back(temp);
	

	temp.setCharacterSize(30);

	temp.setString("Selecionar Fase");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25);
	texto.push_back(temp);

	temp.setString("Carregar Jogo");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45);
	texto.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 2);
	texto.push_back(temp);
}

void Menu::desenharTexto() {
	if (GG) {
		for (int i = 0; i < (int)texto.size(); i++) {
			texto[i].setPosition(GG->getCamera().getCenter().x - texto[i].getLocalBounds().width / 2, texto[i].getPosition().y);
			if (i == selecionado) {
				texto[i].setFillColor(sf::Color(sf::Color(99, 162, 121)));
			}
			else {
				texto[i].setFillColor(sf::Color(sf::Color::White));
			}
			GG->desenharTexto(texto[i]);
		}
	}
	else {
		std::cout << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
}

void Menu::operator++() {
	selecionado = (selecionado + 1) % (int)texto.size();
	if (0 == selecionado) {
		selecionado = 1;
	}
}

void Menu::operator--() {
	if (1 == selecionado) {
		selecionado = (int)texto.size();
	}
	selecionado--;
}

void Menu::selecionar() {
	executa = true;
}

void Menu::setJogo(Jogo* jogo) {
	pJog = jogo;
}
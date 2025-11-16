#include "Menu_Pause.h"
#include "Jogo.h"

Menu_Pause::Menu_Pause() :
	Menu()
{
	inicializaFundo();
	inicializaTexto();
}

Menu_Pause::~Menu_Pause()
{}

void Menu_Pause::executar() {
	parar = false;
	while (!parar) {
		if (GG) {
			if (GE) {
				executa = false;
				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 1, GG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenu(static_cast<Menu*>(this));	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				desenharTexto();
				GG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (1 == selecionado) {
							pJog->setEstadoMenuPrincipal();
							parar = true;
						}
						else if (2 == selecionado) {
							pJog->voltarEstado();
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

void Menu_Pause::inicializaFundo() {
	// Pensei de fazer um rand com esse fundo e o fundo da fase 2
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

void Menu_Pause::inicializaTexto() {
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
	temp.setString("Menu Principal");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25);
	texto.push_back(temp);

	temp.setString("Voltar");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45);
	texto.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 2);
	texto.push_back(temp);
}
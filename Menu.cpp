#include "Menu.h"
#include "Jogo.h"

Menu::Menu() :
	Ente(),
	pJog(nullptr),
	GG(GG->getGerenciadorGrafico()),
	GE(GE->getGerenciadorEventos()),
	fundo()
{
	inicializaFundo();
}

Menu::~Menu() {
	pJog = nullptr;
	GG = nullptr;
	GE = nullptr;
}

void Menu::executar() {
	while (GG->verificaJanelaAberta()) {
		if (GG) {
			if (GE) {
				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 0.008, GG->getCamera().getCenter().y));	// "Anda"
				GE->executar();	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				GG->mostrarEntes();
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
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada1.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada2.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada3.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada4.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada5.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada6.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada7.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada8.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0000005f, "Imagens/JapanVillage/Camada9.png");
	fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize().x, GG->getWindow()->getSize().y - 80.0f));	// Chao
}
#include "Menu.h"
#include "Jogo.h"

Menu::Menu() :
	Ente(),
	pJog(nullptr),
	GG(GG->getGerenciadorGrafico()),
	GE(GE->getGerenciadorEventos()),
	fundo(),
	fonte(),
	texto()
{
	inicializaFundo();
	inicializaTexto();
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
				desenharTexto();
				GG->mostrarEntes();	// Display
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

void Menu::inicializaTexto() {
	texto.clear();
	fonte.loadFromFile("Fonte/determination.ttf");

	sf::Text temp;
	temp.setString("Iniciar Jogo");
	temp.setCharacterSize(25);
	temp.setFillColor(sf::Color::White);
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(2);
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 30);
	temp.setFont(fonte);
	texto.push_back(temp);

	sf::Text temp2;
	temp2.setString("Salvar Jogo");
	temp2.setCharacterSize(25);
	temp2.setFillColor(sf::Color::White);
	temp2.setOutlineColor(sf::Color::Black);
	temp2.setOutlineThickness(2);
	temp2.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 50);
	temp2.setFont(fonte);
	texto.push_back(temp);
}

void Menu::desenharTexto() {
	if (GG) {
		for (int i = 0; i < (int)texto.size(); i++) {
			texto[0].setPosition(GG->getCamera().getCenter().x - texto[i].getLocalBounds().width / 2, texto[i].getPosition().y);
			GG->desenharTexto(texto[i]);
		}
	}
	else {
		std::cout << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
}
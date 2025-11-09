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
	fonte.loadFromFile("Fonte/superstar_memesbruh03.ttf");

	sf::Text temp;
	temp.setString("NOME DO JOGO");
	temp.setCharacterSize(85);
	temp.setFillColor(sf::Color(sf::Color::White));
	//temp.setFillColor(sf::Color(sf::Color(255, 209, 230)));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 150);
	temp.setFont(fonte);
	texto.push_back(temp);
	

	temp.setCharacterSize(30);
	temp.setString("Fase 1");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 35);
	texto.push_back(temp);

	temp.setString("Fase 2");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 35 + 45);
	texto.push_back(temp);

	temp.setString("Salvar Jogo");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 35 + 45 * 2);
	texto.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 35 + 45 * 3);
	texto.push_back(temp);
}

void Menu::desenharTexto() {
	if (GG) {
		for (int i = 0; i < (int)texto.size(); i++) {
			texto[i].setPosition(GG->getCamera().getCenter().x - texto[i].getLocalBounds().width / 2, texto[i].getPosition().y);
			GG->desenharTexto(texto[i]);
		}
	}
	else {
		std::cout << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
}
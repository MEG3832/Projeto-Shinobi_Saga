#include "Menu.h"
#include "Jogo.h"

Jogo* Menu::pJog = nullptr;

void Menu::setJogo(Jogo* jogo) {
	pJog = jogo;
}

Menu::Menu() :
	Ente(),
	GE(GE->getGerenciadorEventos()),
	fundo(),
	fonte(),
	texto(),
	titulo(),
	selecionado(1),
	parar(false),
	executa(false)
{
	fonte.loadFromFile("Fonte/superstar_memesbruh03.ttf");

	titulo.setString("Shinobi Saga");
	titulo.setCharacterSize(70);
	titulo.setFillColor(sf::Color(sf::Color::White));
	titulo.setOutlineColor(sf::Color::Black);
	titulo.setOutlineThickness(4);
	titulo.setPosition(pGG->getCamera().getCenter().x - titulo.getLocalBounds().width / 2, pGG->getCamera().getCenter().y - 160);
	titulo.setFont(fonte);

	inicializaFundo();
}

Menu::~Menu() {
	pJog = nullptr;
	GE = nullptr;
	selecionado = -1;
	parar = false;
	executa = false;
	texto.clear();
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

void Menu::desenharTexto() {
	if (pGG) {
		for (int i = 0; i < (int)texto.size(); i++) {
			texto[i].setPosition(pGG->getCamera().getCenter().x - texto[i].getLocalBounds().width / 2, texto[i].getPosition().y);
			if (i == selecionado) {
				texto[i].setFillColor(sf::Color(sf::Color(99, 162, 121)));
			}
			else {
				texto[i].setFillColor(sf::Color(sf::Color::White));
			}
			pGG->desenharTexto(texto[i]);
		}
	}
	else {
		std::cerr << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
}

void Menu::operator++() {
	selecionado = (selecionado + 1) % (int)texto.size();
}

void Menu::operator--() {
	if (0 == selecionado) {
		selecionado = (int)texto.size();
	}
	selecionado--;
}

void Menu::selecionar() {
	executa = true;
}
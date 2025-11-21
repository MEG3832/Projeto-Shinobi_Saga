#include "Menu.h"
#include "Jogo.h"

Jogo* Menu::pJog = nullptr;
Entidades::Personagens::Jogador* Menu::pJog1 = nullptr;
Entidades::Personagens::Jogador* Menu::pJog2 = nullptr;

void Menu::setJogo(Jogo* jogo) {
	pJog = jogo;
}

void Menu::setJogador1(Entidades::Personagens::Jogador* pJ) {
	pJog1 = pJ;
}

void Menu::setJogador2(Entidades::Personagens::Jogador* pJ) {
	pJog2 = pJ;
}

Menu::Menu() :
	Ente(),
	GG(GG->getGerenciadorGrafico()),
	GE(GE->getGerenciadorEventos()),
	fundo(),
	fonte(),
	texto(),
	selecionado(1),
	executa(false),
	parar(false)
{
	fonte.loadFromFile("Fonte/superstar_memesbruh03.ttf");

	inicializaFundo();
}

Menu::~Menu() {
	pJog = nullptr;
	GG = nullptr;
	GE = nullptr;
	selecionado = -1;
	executa = false;
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
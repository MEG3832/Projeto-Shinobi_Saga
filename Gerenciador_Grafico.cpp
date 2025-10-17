#include "Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico() :
	window(new sf::RenderWindow(sf::VideoMode(800.0f,600.0f), "Nome do Jogo"))
{}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
	if (window) {
		delete(window);
		window = nullptr;
	}
}

void Gerenciador_Grafico::desenharEnte(sf::CircleShape corpo) {
	window->draw(corpo);
}

void Gerenciador_Grafico::mostrarEntes() {
	window->display();
}

sf::RenderWindow* Gerenciador_Grafico::getWindow() {
	return window;
}

const bool Gerenciador_Grafico::verificaJanelaAberta() {
	return window->isOpen();
}

void Gerenciador_Grafico::limpaJanela() {
	window->clear();
}

void Gerenciador_Grafico::fecharJanela() {
	window->close();
}
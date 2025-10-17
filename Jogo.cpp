#include "Jogo.h"

Jogo::Jogo() :
	GG(new Gerenciador_Grafico()), Figura()
{
	Ente::setGG(GG);
	executar();
}

Jogo::~Jogo() {}

void Jogo::executar() {
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	while (GG->verificaJanelaAberta()) {
		sf::Event evento;
		if (GG->getWindow()->pollEvent(evento)) {
			if (evento.type == sf::Event::Closed()) {
				GG->fecharJanela();
			}
			else if (evento.type == sf::Event::KeyPressed) {
				if (evento.key.code == sf::Keyboard::Escape) {
					GG->fecharJanela();
				}
			}
		}
		GG->limpaJanela();
		Figura.desenhar();
		GG->mostrarEntes();
	}
}
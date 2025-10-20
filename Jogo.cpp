#include "Jogo.h"

Jogo::Jogo() :
	GG(new Gerenciador_Grafico()), fundo()
{
	std::cout << "entrei" << std::endl;
	Ente::setGG(GG);
	executar();
}

Jogo::~Jogo() {}

void Jogo::executar() {
	if (GG) {
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
			fundo.executar();
			GG->mostrarEntes();
		}
	}
}
#include "Jogo.h"

Jogo::Jogo() :
	GG(nullptr), fundo(nullptr)
{
	GG = new Gerenciador_Grafico();
	Ente::setGG(GG);
	fundo = new Fundo();
	executar();
}

Jogo::~Jogo() {
	if(GG) delete GG;
	if (fundo) delete fundo;
	GG = nullptr;
	fundo = nullptr;
}

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
			fundo->executar();
			GG->mostrarEntes();
		}
	}
}
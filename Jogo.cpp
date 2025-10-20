#include "Jogo.h"

Jogo::Jogo() :
	GG(GG->getGerenciadorGrafico()), fundo(nullptr)
{
	Ente::setGG(GG);
	fundo = new Fundo();
	executar();
}

Jogo::~Jogo() {

    if(GG) delete GG;
    GG = nullptr;
	if (fundo) delete fundo;
	fundo = nullptr;
}

void Jogo::executar() {
    int frame = 0;
    sf::Vector2f pos = GG->getCamera().getCenter();
    if (GG) {
        while (GG->verificaJanelaAberta()) {
            frame++;
            // Processar eventos
            sf::Event evento;
            while (GG->getWindow()->pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    GG->fecharJanela();
                }
            }

            GG->limpaJanela();

            if (fundo) {
                fundo->executar();
            }
            else {
                std::cerr << "Fundo eh NULL" << std::endl;
            }

            GG->mostrarEntes();

            GG->atualizaCamera(pos);
            pos.x += 0.005;
            pos.y += 0.005;
            //if (frame > 10) break;
        }
    }
}
#include "Jogo.h"

Jogo::Jogo() :
	GG(GG->getGerenciadorGrafico()), 
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    Figura()
{
	executar();
}

Jogo::~Jogo() {

    if(GG) delete GG;
    GG = nullptr;
}

void Jogo::executar() {
    sf::Vector2f pos = GG->getCamera().getCenter(); // Teste
    if (GG) {
        while (GG->verificaJanelaAberta()) {
            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            sf::Event evento;
            while (GG->getWindow()->pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    GG->fecharJanela();
                }
            }

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem
            GG->atualizaCamera(pos);

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            fundo.executar();
            //Figura.desenhar();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
            pos.x += 0.005;
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
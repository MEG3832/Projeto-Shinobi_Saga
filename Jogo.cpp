#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    jogador(), 
    GE(GE->getGerenciadorEventos())
    //lista_ents()
{
    GE->setJogador(&jogador);
	executar();
}

Jogo::~Jogo() {

    if(GG) delete GG;
    GG = nullptr;
}

void Jogo::executar() {
    if (GG) {
        while (GG->verificaJanelaAberta()) {
            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            GE->executar();

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem

            jogador.desenhar();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            //fundo.executar();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
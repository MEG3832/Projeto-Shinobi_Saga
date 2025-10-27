#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    jogador(), 
    GE(GE->getGerenciadorEventos()),
    inimigo(),
    obstaculo(),
    GC(GC->getGerenciadorColisoes(&jogador))
    //lista_ents()
{
    GE->setJogador(&jogador);

    inicializar();
	executar();
}

Jogo::~Jogo() {

    if(GG) delete GG;
    GG = nullptr;
    if (GG) delete GE;
    GE = nullptr;
    if (GC) delete GC;
    GC = nullptr;
}

void Jogo::inicializar() {
    inicializaListaEntidades();

    inicializarListaInimigos();

    inicializarListaObtaculos();
    
    inicializarListaProjeteis();
}

void Jogo::inicializaListaEntidades() {
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&jogador)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(&obstaculo));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(&projetil));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&inimigo)));
}

void Jogo::inicializarListaInimigos() {
    GC->incluirInimigo(&inimigo);
}

void Jogo::inicializarListaObtaculos() {
    GC->incluirObstaculo(&obstaculo);
}

void Jogo::inicializarListaProjeteis() {
    GC->incluirProjetil(&projetil);
}

void Jogo::executar() {
    if (GG) {
        while (GG->verificaJanelaAberta()) {
            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            GE->executar();

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem

            lista_ents.desenharEntidades();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            //fundo.executar();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
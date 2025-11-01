#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    jogador(), 
    GE(GE->getGerenciadorEventos()),
    inimigo(&jogador), //pode fazer isso, né?
    obstaculo(),
    GC1(new Gerenciadores::Gerenciador_Colisoes(fundo.getChao())),
    lista_ents()
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
    if (GC1) delete GC1;
    GC1 = nullptr;
}

void Jogo::inicializar() {
    inicializarGC();

    inicializaListaEntidades();
}

void Jogo::inicializarGC() {
    GC1->setJogador(&jogador);

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
    GC1->incluirInimigo(&inimigo);
}

void Jogo::inicializarListaObtaculos() {
    GC1->incluirObstaculo(&obstaculo);
}

void Jogo::inicializarListaProjeteis() {
    GC1->incluirProjetil(&projetil);
}

void Jogo::executar() { // Desenha 4 retangulos e o fundo
    if (GG) {
        while (GG->verificaJanelaAberta()) {
            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            GE->executar();

            //coloquei o executar de inimigo:

            inimigo.executar();

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem
            GG->atualizaCamera(jogador.getPos());

            GC1->executar();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            fundo.executar();
            
            jogador.atualizaAnimacao();

            lista_ents.desenharEntidades();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
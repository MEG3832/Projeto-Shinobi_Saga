#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    jogador(), 
    GE(GE->getGerenciadorEventos()),
    inimigo(),
    plataforma(),
    redemoinho(),
    armadilha_de_urso(),
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
        static_cast<Entidades::Obstaculos::Obstaculo*>(&plataforma)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
        static_cast<Entidades::Obstaculos::Obstaculo*>(&redemoinho)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
        static_cast<Entidades::Personagens::Personagem*>(&jogador)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
        static_cast<Entidades::Obstaculos::Obstaculo*>(&armadilha_de_urso)));
}

void Jogo::inicializarListaInimigos() {
    //GC1->incluirInimigo(&inimigo);
}

void Jogo::inicializarListaObtaculos() {
    GC1->incluirObstaculo(&plataforma);
    GC1->incluirObstaculo(&redemoinho);
    GC1->incluirObstaculo(&armadilha_de_urso);
}

void Jogo::inicializarListaProjeteis() {
    //GC1->incluirProjetil(&projetil);
}

void Jogo::executar() { // Desenha 4 retangulos e o fundo
    if (GG) {
        while (GG->verificaJanelaAberta()) {
            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            GE->executar();

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem
            GG->atualizaCamera(jogador.getPos());

            GC1->executar();

            lista_ents.percorrer();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            fundo.executar();
            
            jogador.atualizaAnimacao();

            redemoinho.atualizaAnimacao();

            lista_ents.desenharEntidades();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
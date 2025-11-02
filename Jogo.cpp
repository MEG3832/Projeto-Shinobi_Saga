#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    pJog1(),
    GE(GE->getGerenciadorEventos()),
<<<<<<< HEAD
    inimigo(),
    plataforma(),
    redemoinho(),
    armadilha_de_urso(),
    GC(GC->getGerenciadorColisoes(fundo.getChao())),
=======
    inimigo(&jogador), //pode fazer isso, né?
    obstaculo(),
    GC1(new Gerenciadores::Gerenciador_Colisoes(fundo.getChao())),
>>>>>>> jogador-e-inimigo
    lista_ents()
{
    GE->setJogador(&pJog1);

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
    inicializarGC();

    inicializaListaEntidades();
}

void Jogo::inicializarGC() {
    GC->setJogador(&pJog1);

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
        static_cast<Entidades::Personagens::Personagem*>(&pJog1)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
        static_cast<Entidades::Obstaculos::Obstaculo*>(&armadilha_de_urso)));
}

void Jogo::inicializarListaInimigos() {
    //GC1->incluirInimigo(&inimigo);
}

void Jogo::inicializarListaObtaculos() {
    GC->incluirObstaculo(&plataforma);
    GC->incluirObstaculo(&redemoinho);
    GC->incluirObstaculo(&armadilha_de_urso);
}

void Jogo::inicializarListaProjeteis() {
    //GC->incluirProjetil(&projetil);
}

void Jogo::executar() { // Desenha 4 retangulos e o fundo
    if (GG) {
        while (GG->verificaJanelaAberta()) {

            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            GE->executar();

            //coloquei o executar de inimigo:

            inimigo.executar();

            jogador.mover(); //chamamos o mover no loop pq precisamos q o "knockback" seja processado mesmo que não estejamos
                             //apertando uma tecla!
           

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem
            GG->atualizaCamera(pJog1.getPos());

            GC->executar();

            lista_ents.percorrer();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            fundo.executar();
            
            pJog1.atualizaAnimacao();



            //teste
            sf::RectangleShape* corpoTengu = inimigo.getCorpo();

            sf::RectangleShape debugHitbox = *corpoTengu;

            debugHitbox.setTexture(nullptr);
            debugHitbox.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente

            
            GG->getWindow()->draw(debugHitbox);

            

            lista_ents.desenharEntidades();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
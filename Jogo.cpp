#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    pJog1(),
    GE(GE->getGerenciadorEventos()),
    plataforma(),
    redemoinho(),
    armadilha_de_urso(),
    inimigo(&pJog1, 50.0),
    GC(GC->getGerenciadorColisoes()),
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
    inicializaFundo();

    inicializarGC();

    inicializaListaEntidades();
}

void Jogo::inicializarGC() {
    GC->setJogador(&pJog1);

    GC->setChao(fundo.getChao());

    //inicializarListaInimigos();

    //inicializarListaObtaculos();

    //inicializarListaProjeteis();
}

void Jogo::inicializaListaEntidades() {
    //lista_ents.incluir(static_cast<Entidades::Entidade*>(
    //                  static_cast<Entidades::Obstaculos::Obstaculo*>(&plataforma)));
    //lista_ents.incluir(static_cast<Entidades::Entidade*>(
    //                   static_cast<Entidades::Obstaculos::Obstaculo*>(&redemoinho)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&pJog1)));
    //lista_ents.incluir(static_cast<Entidades::Entidade*>(
    //                   static_cast<Entidades::Obstaculos::Obstaculo*>(&armadilha_de_urso)));
    //lista_ents.incluir(static_cast<Entidades::Entidade*>(
    //                   static_cast<Entidades::Personagens::Personagem*>(&inimigo)));
}

void Jogo::inicializarListaInimigos() {
    GC->incluirInimigo(&inimigo);
}

void Jogo::inicializarListaObtaculos() {
    GC->incluirObstaculo(&plataforma);
    //GC->incluirObstaculo(&redemoinho);
    //GC->incluirObstaculo(&armadilha_de_urso);
}

void Jogo::inicializarListaProjeteis() {
    //GC->incluirProjetil(&projetil);
}

void Jogo::executar() { // Desenha 4 retangulos e o fundo
    if (GG) {
        //menu.executar();

        while (GG->verificaJanelaAberta()) {

            // Processar eventos (no momento só fecha clicando no X). Vamos fazer um Gerenciador de Eventos pra ver isso
            GE->executar();

            GG->limpaJanela();

            // Atualizar a câmera aqui, passando como parâmetro a posição do personagem
            GG->atualizaCamera(pJog1.getPos());

            pJog1.sofrerGravidade();    // Queria colocar na lista

            GC->executar();

            lista_ents.percorrer();

            GC->executar();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            fundo.executar();

            lista_ents.desenharEntidades();

            //teste
            /*sf::RectangleShape* corpoJogador = pJog1.getHitBox();
            sf::RectangleShape* corpoInim = inimigo.getHitBox();

            sf::RectangleShape debugHitbox = *corpoJogador;
            sf::RectangleShape debugHitbox2 = *corpoInim;

            debugHitbox.setTexture(nullptr);
            debugHitbox.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente

            debugHitbox2.setTexture(nullptr);
            debugHitbox2.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente

            GG->getWindow()->draw(debugHitbox);
            GG->getWindow()->draw(debugHitbox2);

            if (pJog1.getHitboxAtaqueAtiva()) {
                sf::RectangleShape debugAtaque = *pJog1.getHitboxAtaque();
                debugAtaque.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho transparente
                GG->getWindow()->draw(debugAtaque);
            }

            /*sf::RectangleShape* corpo2 = plataforma.getHitBox();

            sf::RectangleShape debugHitbox1 = *corpo2;

            debugHitbox1.setTexture(nullptr);
            debugHitbox1.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente

            GG->getWindow()->draw(debugHitbox1);*/



            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}

void Jogo::inicializaFundo() {
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada1.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada2.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada3.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada4.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada5.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada6.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada7.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada8.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize()), 0.0000005f, "Imagens/JapanVillage/Camada9.png");
    fundo.addCamada(sf::Vector2f(GG->getWindow()->getSize().x, GG->getWindow()->getSize().y - 80.0f));	// Chao
}
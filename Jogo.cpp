#include "Jogo.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr),
    menu(),
<<<<<<< HEAD
    estado_atual(MENU_PRINCIPAL)
{
    srand(time(0));
=======
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    pJog1(),
    GE(GE->getGerenciadorEventos()),
    plataforma(),
    redemoinho(),
    armadilha_de_urso(),
    inimigo(&pJog1),
    projetil(&inimigo),
    GC(GC->getGerenciadorColisoes()),
    lista_ents(),
    fase(1)
{
    inimigo.setProjetil(&projetil);

    GE->setJogador(&pJog1);
>>>>>>> chefao

    if (!pGG)
    {
        std::cout << "ERRO! O ponteiro Gerenc. Grafico NAO pôde ser inicializado..." << std::endl;
        exit(1);
    }

    if (!pGE)
    {
        std::cout << "ERRO! O ponteiro Gerenc. de Eventos NAO pôde ser inicializado..." << std::endl;
        exit(1);
    }

    pGG->getWindow()->setFramerateLimit(60);

    Ente::setGG(pGG);

    criarFase();
    
    pGE->setJogador(static_cast<Fases::FasePrimeira*>(pFase1)->getJogador());

    menu.setJogo(this);

}

<<<<<<< HEAD
Jogo::~Jogo()
{
    // Limpa a fase (que limpa suas listas, etc.)
    if (pFase1) {
        delete pFase1;
        pFase1 = nullptr;
    }
    if (pGG) {
        delete pGG;
        pGG = nullptr;
    }
    if (pGE) {
        delete pGE;
        pGE = nullptr;
    }
}

void Jogo::criarFase()
{
    pFase1 = new Fases::FasePrimeira();
=======
void Jogo::inicializarGC() {
    GC->setJogador(&pJog1);

    GC->setChao(fundo.getChao());

    inicializarListaInimigos();

    //inicializarListaObtaculos();

    inicializarListaProjeteis();
}

void Jogo::inicializaListaEntidades() {
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                      static_cast<Entidades::Obstaculos::Obstaculo*>(&plataforma)));
    //lista_ents.incluir(static_cast<Entidades::Entidade*>(
    //                   static_cast<Entidades::Obstaculos::Obstaculo*>(&redemoinho)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&pJog1)));
    //lista_ents.incluir(static_cast<Entidades::Entidade*>(
    //                   static_cast<Entidades::Obstaculos::Obstaculo*>(&armadilha_de_urso)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&inimigo)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
        static_cast<Entidades::Projetil*>(&projetil)));
>>>>>>> chefao
}

void Jogo::executar()
{
    if (pGG) {
        if (MENU_PRINCIPAL == estado_atual) {
            menu.executar();
        }

<<<<<<< HEAD
        while (pGG->verificaJanelaAberta())
        {

            if (pGE) {
                pGE->executar();
            }
=======
void Jogo::inicializarListaObtaculos() {
    //GC->incluirObstaculo(&plataforma);
    //GC->incluirObstaculo(&redemoinho);
    //GC->incluirObstaculo(&armadilha_de_urso);
}

void Jogo::inicializarListaProjeteis() {
    GC->incluirProjetil(&projetil);
}
>>>>>>> chefao

            // Limpa a tela
            pGG->limpaJanela();

<<<<<<< HEAD
            //executa a lógica da fase 
            //(que chama pFundo->executar(), lista_ents->percorrer() (percorre chamando oexecutar das entidade), GC->executar(), lista_ents->desenharEntidades())
            if (FASE1 == estado_atual) {
                if (pFase1)
                {
                    pFase1->executar();
=======
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

                sf::RectangleShape* corpoProj = projetil.getHitBox();
                sf::RectangleShape* corpoinim = inimigo.getHitBox();

                sf::RectangleShape debugHitbox = *corpoProj;
                sf::RectangleShape debugHitbox2 = *corpoinim;

                debugHitbox.setTexture(nullptr);
                debugHitbox.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente

                debugHitbox2.setTexture(nullptr);
                debugHitbox2.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente

                GG->getWindow()->draw(debugHitbox);
                GG->getWindow()->draw(debugHitbox2);

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
>>>>>>> chefao
                }

                else {
                    std::cerr << "ERRO: Nao eh possivel executar a primeira fase pois ela eh NULL" << std::endl;
                }
            }

            pGG->mostrarEntes();
        }
    }
    else {
        std::cerr << "ERRO: Nao eh possivel executar o jogo pois o Gerenciador Grafico eh NULL" << std::endl;
    }
}

void Jogo::setFase(int num) {
    if (1 == num) {
        estado_atual = FASE1;
    }
    else if (2 == num) {
        estado_atual = FASE2;
    }
}
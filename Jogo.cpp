#include "Jogo.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr)
    menu(),
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    pJog1(),
    GE(GE->getGerenciadorEventos()),
    plataforma(),
    redemoinho(),
    armadilha_de_urso(),
    inimigo(&pJog1, 50.0),
    GC(GC->getGerenciadorColisoes()),
    lista_ents(),
    fase(1)
{
    srand(time(0));

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

}

Jogo::~Jogo()
{
    // Limpa a fase (que limpa suas listas, etc.)
    if (pFase1) {
        delete pFase1;
        pFase1 = nullptr;
    }
}

void Jogo::criarFase()
{
    // Cria a primeira fase
   // o construtor de FasePrimeira vai criar o cenário, inimigos, etc.
    pFase1 = new Fases::FasePrimeira();
}

void Jogo::executar()
{
    while (pGG->verificaJanelaAberta())
    {
        if (pGE) {
            pGE->executar();
        }
    
        // Limpa a tela
        pGG->limpaJanela();

        //executa a lógica da fase 
        //(que chama pFundo->executar(), lista_ents->percorrer() (percorre chamando oexecutar das entidade), GC->executar(), lista_ents->desenharEntidades())
        if (pFase1)
        {
            pFase1->executar();
        }

        pGG->mostrarEntes();
    }
}
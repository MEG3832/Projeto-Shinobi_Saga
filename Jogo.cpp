#include "Jogo.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr),
    pFase2(nullptr),
    pJog1(nullptr),
    pJog2(nullptr),
    menu(),
    estado_atual(MENU_PRINCIPAL)
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

    menu.setJogo(this);

}

Jogo::~Jogo()
{

    // deleta as fases (se existirem)
    if (pFase1)
    {
        delete pFase1;
        pFase1 = nullptr;
    }
    if (pFase2)
    {
        delete pFase2;
        pFase2 = nullptr;
    }
    // deleta os jogadores (O Jogo é o "dono" deles)
    if (pJog1)
    {
        delete pJog1;
        pJog1 = nullptr;
    }
    if (pJog2)
    {
        delete pJog2;
        pJog2 = nullptr;
    }
    //deleta os gerenciadores...
    if (pGG) {
        delete pGG;
        pGG = nullptr;
    }
    if (pGE) {
        delete pGE;
        pGE = nullptr;
    }
}

void Jogo::executar()
{
    if (pGG) {
        if (MENU_PRINCIPAL == estado_atual) {
            menu.executar();
        }

        while (pGG->verificaJanelaAberta())
        {

            if (pGE) {
                pGE->executar();
            }

            // Limpa a tela
            pGG->limpaJanela();

            //executa a lógica da fase 
            //(que chama pFundo->executar(), lista_ents->percorrer() (percorre chamando oexecutar das entidade), GC->executar(), lista_ents->desenharEntidades())
            if (FASE1 == estado_atual) {

                if (pFase2) {
                    delete pFase2;
                    pFase2 = nullptr;
                }
                if (!pFase1) {

                    pJog1 = new Entidades::Personagens::Jogador(1);

                    //if(...) se escolheu jogar com 2 jogadores...
                    pJog2 = new Entidades::Personagens::Jogador(2);

                    pFase1 = new Fases::FasePrimeira(pJog1,pJog2);
                    pGE->setJogador1(pJog1);
                    pGE->setJogador2(pJog2);
                }

                if (pFase1)
                {
                    pFase1->executar();
                }
                else {
                    std::cerr << "ERRO: Nao eh possivel executar a primeira fase pois ela eh NULL" << std::endl;
                }
            }

            if (FASE2 == estado_atual) {
                if (pFase1) {
                    delete pFase1;
                    pFase1 = nullptr;
                }
                if (!pFase2) {

                    pJog1 = new Entidades::Personagens::Jogador(1);

                    //if(...) se escolheu jogar com 2 jogadores...
                    pJog2 = new Entidades::Personagens::Jogador(2);

                    pFase2 = new Fases::FaseSegunda(pJog1,pJog2);
                    pGE->setJogador1(pJog1);
                    pGE->setJogador2(pJog2);
                }

                if (pFase2)
                {
                    pFase2->executar();
                }
                else {
                    std::cerr << "ERRO: Nao eh possivel executar a segunda fase pois ela eh NULL" << std::endl;
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
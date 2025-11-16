#include "Jogo.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr),
    menu(),
    menu_fase(),
    estado_atual(MENU_PRINCIPAL),
    estado_anterior(MENU_PRINCIPAL)
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

    menu.setJogo(this);
    menu_fase.setJogo(this);

}

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
}

void Jogo::executar()
{
    if (pGG) {

        while (pGG->verificaJanelaAberta())
        {
            if (MENU_PRINCIPAL == estado_atual) {
                menu.executar();
            }

            else if (MENU_FASE == estado_atual) {
                menu_fase.executar();
            }

            if (pGE) {
                pGE->executar();
            }

            // Limpa a tela
            pGG->limpaJanela();

            //executa a lógica da fase 
            //(que chama pFundo->executar(), lista_ents->percorrer() (percorre chamando oexecutar das entidade), GC->executar(), lista_ents->desenharEntidades())
            if (FASE1 == estado_atual) {
                if (pFase1)
                {
                    pFase1->executar();
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
        estado_anterior = estado_atual;
        estado_atual = FASE1;
    }
    else if (2 == num) {
        estado_anterior = estado_atual;
        estado_atual = FASE2;
    }
}

void Jogo::setEstadoMenuFases() {
    estado_anterior = estado_atual;
    estado_atual = MENU_FASE;
}

void Jogo::voltarEstado() {
    estado_atual = estado_anterior;
}
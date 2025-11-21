#include "Jogo.h"

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr),
    pFase2(nullptr),
    pJog1(nullptr),
    pJog2(nullptr),
    menu_principal(),
    menu_pause(),
    estado_atual(MENU_PRINCIPAL),
    estado_anterior(MENU_PRINCIPAL)
{
    srand((unsigned int)time(0));

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

    pJog1 = new Entidades::Personagens::Jogador();
    pGE->setJogador(pJog1);
    Menu::setJogador1(pJog1);

    pGG->getWindow()->setFramerateLimit(60);

    pGE->setJogo(this);

    Ente::setGG(pGG);

    Menu::setJogo(this);
    // Jogador2 = nullptr

}

Jogo::~Jogo()
{
    // Limpa a fase (que limpa suas listas, etc.)
    if (pFase1) {
        delete pFase1;
        pFase1 = nullptr;
    }

    if (pFase2) {
        delete pFase2;
        pFase2 = nullptr;
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

void Jogo::executar()
{
    if (pGG) {

        while (pGG->verificaJanelaAberta())
        {
            if (MENU_PRINCIPAL == estado_atual) {
                if (pFase1) {
                    delete pFase1;
                    pFase1 = nullptr;
                    menu_pause.setFase(nullptr);
                }
                if (pFase2) {
                    delete pFase2;
                    pFase2 = nullptr;
                    menu_pause.setFase(nullptr);
                }
                Menu::setJogo(this);
                Menu::setJogador1(pJog1);

                menu_principal.executar();
            }

            else if (MENU_PAUSE == estado_atual) {
                menu_pause.executar();
            }

            else if (FASE1 == estado_atual) {
                if (pFase2) {
                    delete pFase2;
                    pFase2 = nullptr;
                }
                if (!pFase1) {
                    pFase1 = new Fases::FasePrimeira(pJog1);
                    menu_pause.setFase(pFase1);
                }

                if (pFase1)
                {
                    pFase1->executar();
                }
                else {
                    std::cerr << "ERRO: Nao eh possivel executar a primeira fase pois ela eh NULL" << std::endl;
                }
            }

            else if (FASE2 == estado_atual) {
                if (pFase1) {
                    delete pFase1;
                    pFase1 = nullptr;
                }
                if (!pFase2) {
                    pFase2 = new Fases::FaseSegunda(pJog1);
                    menu_pause.setFase(pFase2);
                }

                if (pFase2)
                {
                    pFase2->executar();
                }
                else {
                    std::cerr << "ERRO: Nao eh possivel executar a segunda fase pois ela eh NULL" << std::endl;
                }
            }
        }
    }
    else {
        std::cerr << "ERRO: Nao eh possivel executar o jogo pois o Gerenciador Grafico eh NULL" << std::endl;
    }
}

void Jogo::setEstado(int num) {
    estado_anterior = estado_atual;
    estado_atual = static_cast<Estado>(num);
    if (FASE1 == estado_atual) {
        if (pFase1) {
            menu_pause.setFase(pFase1);
        }
    }
    else if (FASE2 == estado_atual) {
        if (pFase2) {
            menu_pause.setFase(pFase2);
        }
    }
}

void Jogo::voltarEstado() {
    estado_atual = estado_anterior;
}

void Jogo::setFase(Fases::FasePrimeira* pF1, Fases::FaseSegunda* pF2) {
    pFase1 = pF1;
    pFase2 = pF2;
}
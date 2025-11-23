#include "Jogo.h"

Jogo::Jogo() :
    multiplayer(false),
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pGC(pGC->getGerenciadorColisoes()),
    pFase1(nullptr),
    pFase2(nullptr),
    pJog1(nullptr),
    pJog2(nullptr),
    menu_principal(),
    menu_pause(),
    menu_colocacao(),
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

    if (!pGC)
    {
        std::cout << "ERRO! O ponteiro Gerenc. de Colisoes NAO pôde ser inicializado..." << std::endl;
        exit(1);
    }

    pGG->getWindow()->setFramerateLimit(60);

    pGE->setJogo(this);

    Ente::setGG(pGG);

    Menu::setJogo(this);

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
                if (pJog1) {
                    delete pJog1;
                    pJog1 = nullptr;
                    pGE->setJogador1(nullptr);
                    pGC->setJogador1(nullptr);
                }
                if (pJog2) {
                    delete pJog2;
                    pJog2 = nullptr;
                    pGE->setJogador2(nullptr);
                    pGC->setJogador2(nullptr);
                }
                Menu::setJogo(this);

                menu_principal.executar();

                if (!pJog1 && !pJog2) {
                    pJog1 = new Entidades::Personagens::Jogador(1);
                    pGE->setJogador1(pJog1);
                    pGC->setJogador1(pJog1);
                    Menu::setJogador1(pJog1);

                    if (multiplayer) {
                        pJog2 = new Entidades::Personagens::Jogador(2);
                        pGE->setJogador2(pJog2);
                        pGC->setJogador2(pJog2);
                        Menu::setJogador2(pJog2);
                    }
                }
            }

            else if (MENU_PAUSE == estado_atual) {
                menu_pause.executar();
            }

            else if (MENU_COLOCACAO == estado_atual) {
                menu_colocacao.carregar();
                menu_colocacao.executar();
            }

            else if (FASE1 == estado_atual) {
                if (pFase2) {
                    delete pFase2;
                    pFase2 = nullptr;
                }
                if (!pFase1) {
                    if (multiplayer) {
                        pFase1 = new Fases::FasePrimeira(pJog1, pJog2);
                    }
                    else {
                        pFase1 = new Fases::FasePrimeira(pJog1);
                    }
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
                    if (multiplayer) {
                        pFase2 = new Fases::FaseSegunda(pJog1, pJog2);
                    }
                    else {
                        pFase2 = new Fases::FaseSegunda(pJog1);
                    }
                    menu_pause.setFase(pFase2);
                    Menu::setJogo(this);
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

int Jogo::getEstado() {
    return static_cast<int>(estado_atual);
}

void Jogo::voltarEstado() {
    estado_atual = estado_anterior;
}

void Jogo::setFase(Fases::FasePrimeira* pF1, Fases::FaseSegunda* pF2) {
    pFase1 = pF1;
    pFase2 = pF2;
}

bool Jogo::getMultiplayer() {
    return multiplayer;
}

void Jogo::setMultiplayer(bool m) {
    multiplayer = m;
}
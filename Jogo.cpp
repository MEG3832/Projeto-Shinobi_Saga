#include "Jogo.h"

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr),
    menu(),
    menu_fase(),
    menu_pause(),
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

    pGE->setJogo(this);

    Ente::setGG(pGG);

    criarFase();
    
    pGE->setJogador(static_cast<Fases::FasePrimeira*>(pFase1)->getJogador());

    menu.setJogo(this);
    menu_fase.setJogo(this);
    menu_pause.setJogo(this);

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

            else if (MENU_PAUSE == estado_atual) {
                menu_pause.executar();
            }

            else if (FASE1 == estado_atual) {
                if (pFase1)
                {
                    pFase1->executar();
                }

                else {
                    std::cerr << "ERRO: Nao eh possivel executar a primeira fase pois ela eh NULL" << std::endl;
                }
            }
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

void Jogo::setEstadoMenuPause() {
    estado_anterior = estado_atual;
    estado_atual = MENU_PAUSE;
}

void Jogo::setEstadoMenuPrincipal() {
    estado_anterior = estado_atual;
    estado_atual = MENU_PRINCIPAL;
}

void Jogo::voltarEstado() {
    estado_atual = estado_anterior;
}

void Jogo::salvar() {
    if (FASE1 == estado_anterior) {
        if (pFase1) {
            pFase1->salvar();
        }
        else {
            std::cerr << "ERRO: Nao eh possivel salvar pois o ponteiro para a fase 1 eh NULL" << std::endl;
        }
    }
    /*else if (FASE2 == estado_anterior) {
        if (pFase2) {
            pFase2->salvar();
        }
        else {
            std::cerr << "ERRO: Nao eh possivel salvar pois o ponteiro para a fase 2 eh NULL" << std::endl;
        }
    }*/
}

void Jogo::carregar() {

    int fase = 0;

    /* Cria uma instancia de iftream (input file stream), usado para ler o arquivo no disco*/
    std::ifstream ifs("testeSave.json");

    if (ifs.is_open()) {	// Verifica se estah aberto
        try {

            /* Faz o parse, ou seja, lê todos os dados do fluxo ifs, transformando-os em um objeto JSON na memoria*/
            nlohmann::json j = nlohmann::json::parse(ifs);
            ifs.close();	// Fecha o arquivo e para a leitura e analise

            std::cout << "Jogo carregado de: " << "testeSave.json" << std::endl << std::endl;
            /* Acessar o valor associado a chave "fase_atual", transformando-a em um int*/
            try {
                fase = j.at("fase_atual").get<int>();

            }
            catch (const nlohmann::json::out_of_range& e) {
                std::cerr << "ERRO: Chave 'fase_atual' ausente." << e.what() << std::endl;
            }
            

            if (1 == fase) {
                if (pFase1) {
                    pFase1->carregar(j);
                }
                else {
                    std::cerr << "ERRO: Nao eh possivel carrgar pois o ponteiro para a fase 1 eh NULL" << std::endl;
                }
            }
            /*else if (2 == fase) {
                if (pFase2) {
                    pFase2->carregar(j);
                }
                else {
                    std::cerr << "ERRO: Nao eh possivel carregar pois o ponteiro para a fase 2 eh NULL" << std::endl;
                }
            }*/
        }
        catch (const nlohmann::json::parse_error& e) {	// Catch acontece com o erro específico de parsing. O erro eh capturado e armazenado na variavel e
            /* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
            std::cerr << "ERRO: Falha ao analisar o JSON do arquivo. Motivo: " << e.what() << std::endl;
        }
    }
    else {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para carregar." << std::endl;
    }
}
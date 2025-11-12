#include "Jogo.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() :
    pGG(pGG->getGerenciadorGrafico()),
    pGE(pGE->getGerenciadorEventos()),
    pFase1(nullptr)
{
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

        /*sf::RectangleShape* hitBoxAtaque; // Tem a exata posição e tamanho da hitBox de ataque
        hitBoxAtaque = new sf::RectangleShape(sf::Vector2f(32.0f, 23.0f));
        hitBoxAtaque->setFillColor(sf::Color(255, 0, 0, 100));
        //hitBoxAtaque->setPosition(pFase1->getJogador()->getCorpo()->getPosition().x + 42.0f,
        //                          pFase1->getJogador()->getCorpo()->getPosition().y + 35.0f);
        hitBoxAtaque->setPosition(pFase1->getJogador()->getCorpo()->getPosition().x + pFase1->getJogador()->getCorpo()->getSize().x - 75.0f,
            pFase1->getJogador()->getCorpo()->getPosition().y + 35.0f);

        pGG->getWindow()->draw(*hitBoxAtaque);*/

        pGG->mostrarEntes();
    }
}
#include "Jogo.h"

Jogo::Jogo() :
    GG(GG->getGerenciadorGrafico()),
    fundo(),    // O Gerenciador Gráfico é setado na construtora de Ente pelo padrão singleton
    jogador(), 
    GE(GE->getGerenciadorEventos()),
    inimigo(&jogador), //pode fazer isso, né?
    obstaculo(),
    GC1(new Gerenciadores::Gerenciador_Colisoes(fundo.getChao())),
    lista_ents()
{
    GE->setJogador(&jogador);

    inicializar();

	executar();
}

Jogo::~Jogo() {

    if(GG) delete GG;
    GG = nullptr;
    if (GG) delete GE;
    GE = nullptr;
    if (GC1) delete GC1;
    GC1 = nullptr;
}

void Jogo::inicializar() {
    inicializarGC();

    inicializaListaEntidades();
}

void Jogo::inicializarGC() {
    GC1->setJogador(&jogador);

    inicializarListaInimigos();

    inicializarListaObtaculos();

    inicializarListaProjeteis();
}

void Jogo::inicializaListaEntidades() {
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&jogador)));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(&obstaculo));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(&projetil));
    lista_ents.incluir(static_cast<Entidades::Entidade*>(
                       static_cast<Entidades::Personagens::Personagem*>(&inimigo)));
}

void Jogo::inicializarListaInimigos() {
    GC1->incluirInimigo(&inimigo);
}

void Jogo::inicializarListaObtaculos() {
    GC1->incluirObstaculo(&obstaculo);
}

void Jogo::inicializarListaProjeteis() {
    GC1->incluirProjetil(&projetil);
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
            GG->atualizaCamera(jogador.getPos());

            GC1->executar();

            // O executar do fundo vai desenhar cada uma de suas camada na posição correta, segundo a posição da câmera
            fundo.executar();
            
            jogador.atualizaAnimacao();



            // --- CÓDIGO DE TESTE DA HITBOX (ADICIONE AQUI) ---

            // 1. Pegamos o 'corpo' original do Tengu (que está na variável 'inimigo')
            //    (Sabemos que getCorpo() existe por causa do Gerenciador_Colisoes)
            sf::RectangleShape* corpoTengu = inimigo.getCorpo();

            // 2. Criamos uma CÓPIA temporária para desenhar
            sf::RectangleShape debugHitbox = *corpoTengu;

            // 3. Estilizamos a cópia:
            debugHitbox.setTexture(nullptr); // Remove a textura (MUITO IMPORTANTE)
            debugHitbox.setFillColor(sf::Color(255, 0, 0, 100)); // Vermelho, semi-transparente
            debugHitbox.setOutlineColor(sf::Color::Red);
            debugHitbox.setOutlineThickness(1.0f);

            // 4. Desenhamos a cópia (o GG deve ter acesso ao getWindow())
            GG->getWindow()->draw(debugHitbox);

            // --- FIM DO CÓDIGO DE TESTE ---



            lista_ents.desenharEntidades();

            GG->mostrarEntes(); // Mostra tudo que foi desenhado na tela
        }
    }
    else {
        std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
    }
}
#include "Menu_Colocacao.h"
#include "Jogo.h"

Menu_Colocacao::Menu_Colocacao() :
	Menu(),
	nomes(),
	texto_colocacao(),
    texto_nomes(),
    texto_pontuacoes(),
    tamanho_rank(5)
{
	
    inicializaTexto();
}

Menu_Colocacao::~Menu_Colocacao() {
	nomes.clear();
	texto_colocacao.clear(); 
    texto_nomes.clear();
    texto_pontuacoes.clear();
}

void Menu_Colocacao::carregar() {

    nomes.clear();
    texto_nomes.clear();
    texto_pontuacoes.clear();

    nlohmann::json leaderboard_array = nlohmann::json::array();

    std::ifstream ifs("arquivo_leaderboard.json");

    if (ifs.is_open()) {
        try {
            // Tenta ler todo o conteúdo como um único array JSON válido
            ifs >> leaderboard_array;
        }
        catch (const nlohmann::json::parse_error& e) {

            std::cerr << "ERRO: Arquivo malformado. Tentando leitura objeto a objeto." << std::endl;
        }
        ifs.close();
    }

    // Itera sobre cada elemento (que é um objeto JSON) dentro do array.
    for (const auto& registro : leaderboard_array) {

        try {
            // Acessa o nome e converte para std::string
            std::string nome = registro.at("nome").get<std::string>();

            // Acessa a pontuação e converte para int
            int pontuacao = registro.at("pontuacao").get<int>();

            nomes.push_back(std::make_pair(pontuacao, nome));
        }
        catch (const nlohmann::json::exception& e) {
            std::cerr << "ERRO: Chave invalida" << e.what() << std::endl;
        }
    }

    std::sort(nomes.begin(), nomes.end(), std::greater<>());

    sf::Text temp;
    temp.setCharacterSize(40);
    temp.setFillColor(sf::Color(sf::Color::White));
    temp.setOutlineColor(sf::Color::Black);
    temp.setOutlineThickness(3);
    temp.setFont(fonte);

    for (int i = 0; i < tamanho_rank && i < (int)nomes.size(); i++) {

        temp.setString(nomes[i].second);
        temp.setPosition(85.0f, 100.0f + 55.0f * i);
        texto_nomes.push_back(temp);

        temp.setString(std::to_string(nomes[i].first));
        temp.setPosition(COMPRIMENTO_TELA - 100.0f, 100.0f + 55.0f * i);
        texto_pontuacoes.push_back(temp);
    }
}

void Menu_Colocacao::inicializaTexto() {
    texto_colocacao.clear();

    if (pGG) {
        sf::Text temp;

        temp.setCharacterSize(40);
        temp.setFillColor(sf::Color(sf::Color::White));
        temp.setOutlineColor(sf::Color::Black);
        temp.setOutlineThickness(3);
        temp.setFont(fonte);

        // TExto nao selecionavel: ranking
        temp.setString("#1");
        temp.setPosition(pGG->getCamera().getCenter().x - 300, 100);
        texto_colocacao.push_back(temp);

        temp.setString("#2");
        temp.setPosition(pGG->getCamera().getCenter().x - 300, 100 + 55);
        texto_colocacao.push_back(temp);

        temp.setString("#3");
        temp.setPosition(pGG->getCamera().getCenter().x - 300, 100 + 55 * 2);
        texto_colocacao.push_back(temp);

        temp.setString("#4");
        temp.setPosition(pGG->getCamera().getCenter().x - 300, 100 + 55 * 3);
        texto_colocacao.push_back(temp);

        temp.setString("#5");
        temp.setPosition(pGG->getCamera().getCenter().x - 300, 100 + 55 * 4);
        texto_colocacao.push_back(temp);

        // Texto selecionavel (estah em Menu)
        temp.setCharacterSize(30);

        temp.setString("Menu Principal");
        temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 125);
        texto.push_back(temp);

        temp.setString("Voltar");
        temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 125 + 45);
        texto.push_back(temp);

        temp.setString("Sair");
        temp.setPosition(pGG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, pGG->getCamera().getCenter().y + 125 + 45 * 2);
        texto.push_back(temp);
    }
}

void Menu_Colocacao::desenharTexto() {
    if (pGG) {

        for (int i = 0; i < (int)texto_colocacao.size(); i++) {
            texto_colocacao[i].setPosition(pGG->getCamera().getCenter().x - 300, texto_colocacao[i].getPosition().y);
            pGG->desenharTexto(texto_colocacao[i]);
        }

        for (int i = 0; i < (int)texto_nomes.size(); i++) {
            texto_nomes[i].setPosition(pGG->getCamera().getCenter().x - 200, texto_nomes[i].getPosition().y);
            pGG->desenharTexto(texto_nomes[i]);

            texto_pontuacoes[i].setPosition(pGG->getCamera().getCenter().x + 200, texto_pontuacoes[i].getPosition().y);
            pGG->desenharTexto(texto_pontuacoes[i]);
        }

    }
    else {
        std::cerr << "ERRO: Nao eh possivel desenhar o texto pois o Gerenciador Grafico eh NULL" << std::endl;
    }
}

void Menu_Colocacao::executar() {
    selecionado = 0;
    parar = false;
    while (!parar) {
        if (pGG) {
            if (GE) {
                executa = false;

                pGG->limpaJanela();
                pGG->atualizaCamera(sf::Vector2f(pGG->getCamera().getCenter().x + 1, pGG->getCamera().getCenter().y));	// "Anda"
                GE->executarMenu(this);

                fundo.executar();	// Imprime as camadas

                desenharTexto();
                Menu::desenharTexto();
                pGG->mostrarEntes();	// Display

                if (executa) {

                    if (pJog) {


                        if (0 == selecionado) {
                            pJog->setEstado(0);	// 0 corresponde ao estado MENU_PRINCIPAL no jogo
                            parar = true;
                        }
                        else if (1 == selecionado) {
                            pJog->voltarEstado();
                            parar = true;
                        }
                        else if (2 == selecionado) {	// Sair
                            parar = true;
                            exit(0);
                        }

                    }
                    else {
                        std::cerr << "ERRO: Nao eh possivel executar o comando pois o jogo eh NULL" << std::endl;
                    }
                }

            }
            else {
                std::cerr << "ERRO: Nao eh possivel criar a tela pois o Gerenciador de Eventos eh NULL" << std::endl;
            }
        }
        else {
            std::cerr << "ERRO: Nao eh possivel imprimir na tela pois o Gerenciador Grafico eh NULL" << std::endl;
        }
    }
}
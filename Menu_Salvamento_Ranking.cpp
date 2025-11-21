#include "Menu_Salvamento_Ranking.h"
#include "Jogo.h"

Menu_Salvamento_Ranking::Menu_Salvamento_Ranking() :
	Menu(),
	nomeJog(""),
	texto_salvamento()
{
	inicializaTexto();
}

Menu_Salvamento_Ranking::~Menu_Salvamento_Ranking() {
	nomeJog = "";
}

void Menu_Salvamento_Ranking::inicializaTexto() {
	texto.clear();
	texto_salvamento.clear();

	sf::Text temp;


	temp.setCharacterSize(45);

	temp.setString("Nome: ");
	temp.setFillColor(sf::Color(sf::Color::White));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 125);
	temp.setFont(fonte);
	texto_salvamento.push_back(temp);

	temp.setString(nomeJog);
	temp.setFillColor(sf::Color(sf::Color(99, 162, 121)));
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 60);
	texto_salvamento.push_back(temp);


	temp.setCharacterSize(30);
	temp.setFillColor(sf::Color::White);

	temp.setString("Menu Principal");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 125);
	texto.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 125 + 45);
	texto.push_back(temp);

	if (pJog) {	// Tirei o else pois estava printando em um momento nada a ver
		if (pJog->getEstado() != 4) {	// Ou seja, a fase atual ñao eh a 2
			temp.setString("Proxima Fase");
			temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 125 + 45 * 2);
			texto.push_back(temp);
		}
	}
}

void Menu_Salvamento_Ranking::executar() {
	selecionado = 0;
	parar = false;
	while (!parar) {
		if (GG) {
			if (GE) {
				executa = false;

				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 1, GG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenuSave(this);

				fundo.executar();	// Imprime as camadas

				texto_salvamento[(int)texto_salvamento.size() - 1].setString(nomeJog);

				desenharTexto();
				Menu::desenharTexto();
				GG->mostrarEntes();	// Display

				if (executa) {

					if (pJog) {

						
						if (0 == selecionado) {
							salvar();
							pJog->setEstado(0);	// 0 corresponde ao estado MENU_PRINCIPAL no jogo
							parar = true;
						}
						else if (1 == selecionado) {
							parar = true;
							exit(0);
						}
						else if (2 == selecionado) {	// Sair
							pJog->setEstado(4);	// 4 corresponde ao estado FASE2 no jogo
							parar = true;
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

void Menu_Salvamento_Ranking::desenharTexto() {
	if (GG) {

		for (int i = 0; i < (int)texto_salvamento.size(); i++) {
			texto_salvamento[i].setPosition(GG->getCamera().getCenter().x - texto_salvamento[i].getLocalBounds().width / 2, texto_salvamento[i].getPosition().y);
			GG->desenharTexto(texto_salvamento[i]);
		}
	}
	else {
		std::cout << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
}

void Menu_Salvamento_Ranking::addCaractere(const char c) {
	nomeJog.push_back(c);
}

void Menu_Salvamento_Ranking::removeCaractere() {
	if ((int)nomeJog.size() > 0) {
		nomeJog.pop_back();
	}
}

void Menu_Salvamento_Ranking::salvar() {

	int pontuacao = 0;

	if (pJog1) {
		pontuacao += pJog1->getPontuacao();
	}
	if (pJog2) {
		pontuacao += pJog2->getPontuacao();
	}

	nlohmann::json buffer = {
		{"nome", nomeJog},
		{"pontuacao", pontuacao}
	};

	std::ofstream arquivo_leaderboard("arquivo_leaderboard.json", std::ios::app);

	if (arquivo_leaderboard.is_open()) {	// Verifica se o arquivo foi aberto
		/* Escreve tudo no arquivo (serializa), com uma indentação de 4 espaços pra tornar mais legível*/
		arquivo_leaderboard << buffer.dump(4);
		arquivo_leaderboard.close();	// Fecha o arquivo e para a escrita

		std::cout << "Pontuacao salva em : " << "arquivo_leaderboard.json" << std::endl;
	}
	else {
		std::cerr << "ERRO: Nao foi possivel abrir o arquivo para salvar a colocacao" << std::endl;
	}
}


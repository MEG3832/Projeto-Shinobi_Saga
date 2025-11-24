#include "Menu_Salvamento_Ranking.h"
#include "Jogo.h"

Menu_Salvamento_Ranking::Menu_Salvamento_Ranking() :
	Menu(),
	nomeJog(""),
	texto_salvamento(),
	podeSeguir(true)
{
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
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 150);
	temp.setFont(fonte);
	texto_salvamento.push_back(temp);

	temp.setString(nomeJog);
	temp.setFillColor(sf::Color(sf::Color(99, 162, 121)));
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 85);
	texto_salvamento.push_back(temp);


	temp.setCharacterSize(30);
	temp.setFillColor(sf::Color::White);

	if (podeSeguir) {	// Ou seja, a fase atual ñao eh a 2
		temp.setString("Proxima Fase");
		temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 125);
		texto.push_back(temp);

		temp.setString("Menu Principal");
		temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 125 + 45);
		texto.push_back(temp);

		temp.setString("Sair");
		temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 125 + 45 * 2);
		texto.push_back(temp);
	}
	else {
		temp.setString("Menu Principal");
		temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 175);
		texto.push_back(temp);

		temp.setString("Sair");
		temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 175 + 45);
		texto.push_back(temp);
	}
}

void Menu_Salvamento_Ranking::executar() {
	inicializaTexto();
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

						if (podeSeguir) {

							if (0 == selecionado) {	// Sair
								pJog->setEstado(4);	// 4 corresponde ao estado FASE2 no jogo
								parar = true;
							}
							if (1 == selecionado) {
								salvar();
								pJog->setEstado(0);	// 0 corresponde ao estado MENU_PRINCIPAL no jogo
								parar = true;
							}
							else if (2 == selecionado) {
								parar = true;
								exit(0);
							}
						}

						else {
							if (0 == selecionado) {
								salvar();
								pJog->setEstado(0);	// 0 corresponde ao estado MENU_PRINCIPAL no jogo
								parar = true;
							}
							else if (1 == selecionado) {
								parar = true;
								exit(0);
							}
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
		std::cerr << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
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

	// Vamos ler o arquivo já existente e adicionar mais um nome no array
	nlohmann::json leaderboard_array = nlohmann::json::array(); // Array que vamos construir/manter

	std::ifstream arquivo_leitura("arquivo_leaderboard.json");

	if (arquivo_leitura.is_open()) {
		try {
			// Tenta ler todo o conteúdo como um único array JSON válido
			arquivo_leitura >> leaderboard_array;
		}
		catch (const nlohmann::json::parse_error& e) {

			std::cerr << "ERRO: Arquivo malformado. Tentando leitura objeto a objeto." << std::endl;
		}
		arquivo_leitura.close();
	}

	// Faz um novo registo
	leaderboard_array.push_back(buffer);

	// Escreve o array completo de volta no arquivo
	std::ofstream arquivo_escrita("arquivo_leaderboard.json");

	if (arquivo_escrita.is_open()) {
		arquivo_escrita << leaderboard_array.dump(4);
		arquivo_escrita.close();
	}
	else {
		std::cerr << "ERRO: Nao foi possivel abrir o arquivo para ESCREVER a colocacao" << std::endl;
	}
}

void Menu_Salvamento_Ranking::setSeguir(bool b) {
	podeSeguir = b;
}


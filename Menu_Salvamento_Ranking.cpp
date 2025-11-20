#include "Menu_Salvamento_Ranking.h"
#include "Jogo.h"

Menu_Salvamento_Ranking::Menu_Salvamento_Ranking() :
	Menu(),
	pJog1(nullptr),
	pJog2(nullptr),
	nomeJog(""),
	texto_salvamento()
{
	inicializaTexto();
}

Menu_Salvamento_Ranking::~Menu_Salvamento_Ranking() {
	pJog1 = nullptr;
	pJog2 = nullptr;
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

	temp.setString("Confirmar");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 150);
	texto.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 150 + 45);
	texto.push_back(temp);
}

void Menu_Salvamento_Ranking::executar() {
	selecionado = 1;
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
							pJog->setEstado(5);	// 5 corresponde ao estado MENU_COLOCACAO
							parar = false;
							// parar = true quando tiver a colocacao
							exit(0);
						}
						else if (1 == selecionado) {	// Sair
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
	nomeJog.pop_back();
}

void Menu_Salvamento_Ranking::salvar() {

}
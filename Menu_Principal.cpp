#include "Menu_Principal.h"
#include "Jogo.h"

Menu_Principal::Menu_Principal() :
	Menu(),
	texto_principal(),
	texto_selecaoFase(),
	texto_selecaoMultiplayer(),
	estado_atual(PRINCIPAL)
{
	inicializaTexto();
}

Menu_Principal::~Menu_Principal() {
	texto_principal.clear();
	texto_selecaoFase.clear();
	texto_selecaoMultiplayer.clear();
	estado_atual = PRINCIPAL;
}

void Menu_Principal::inicializaTexto() {
	inicializaTexto_Principal();
	inicializaTexto_SelecaoFase();
	inicializaTexto_SelecaoMultiplayer();
}

void Menu_Principal::inicializaTexto_SelecaoFase() {
	texto.clear();

	sf::Text temp;
	temp.setString("NOME DO JOGO");
	temp.setCharacterSize(85);
	temp.setFillColor(sf::Color(sf::Color::White));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 150);
	temp.setFont(fonte);
	texto_selecaoFase.push_back(temp);


	temp.setCharacterSize(30);
	temp.setString("Fase 1");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25);
	texto_selecaoFase.push_back(temp);

	temp.setString("Fase 2");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45);
	texto_selecaoFase.push_back(temp);

	temp.setString("Voltar");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 2);
	texto_selecaoFase.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 3);
	texto_selecaoFase.push_back(temp);
}

void Menu_Principal::inicializaTexto_SelecaoMultiplayer() {

}

void Menu_Principal::inicializaTexto_Principal() {
	texto.clear();

	sf::Text temp;
	temp.setString("NOME DO JOGO");
	temp.setCharacterSize(85);
	temp.setFillColor(sf::Color(sf::Color::White));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 150);
	temp.setFont(fonte);
	texto_principal.push_back(temp);


	temp.setCharacterSize(30);

	temp.setString("Selecionar Fase");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25);
	texto_principal.push_back(temp);

	temp.setString("Carregar Jogo");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45);
	texto_principal.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 2);
	texto_principal.push_back(temp);
}

void Menu_Principal::copiarVetores(std::vector<sf::Text> origem, std::vector<sf::Text>* destino) {
	(*destino).clear();
	for (int i = 0; i < (int)origem.size(); i++) {
		(*destino).push_back(origem[i]);
	}
}

void Menu_Principal::executar() {

	parar = false;
	estado_atual = PRINCIPAL;

	while (!parar) {
		if (PRINCIPAL == estado_atual) {
			copiarVetores(texto_principal, &texto);
			executa_Principal();
		}

		else if (SELECAO_FASE == estado_atual) {
			copiarVetores(texto_selecaoFase, &texto);
			executa_SelecaoFase();
		}

		//else {
		// Executar o menu de selecao mutiplayer
		//}
	}
}

void Menu_Principal::executa_Principal() {
	selecionado = 1;
	bool encerrar = false;
	while (!encerrar) {
		if (GG) {
			if (GE) {
				executa = false;
				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 1, GG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenu(this);	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				desenharTexto();
				GG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (1 == selecionado) {
							estado_atual = SELECAO_FASE;
							encerrar = true;
						}
						if (2 == selecionado) {
							pJog->carregar();
							encerrar = true;
							parar = true;
						}
						if (3 == selecionado) {
							encerrar = true;
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

void Menu_Principal::executa_SelecaoFase() {
	selecionado = 1;
	bool encerrar = false;
	while (!encerrar) {
		if (GG) {
			if (GE) {
				executa = false;
				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 1, GG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenu(static_cast<Menu*>(this));	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				desenharTexto();
				GG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (1 == selecionado) {
							pJog->setFase(1);
							encerrar = true;
							parar = true;
						}
						else if (2 == selecionado) {
							pJog->setFase(2);
							encerrar = true;
							parar = true;
						}
						else if (3 == selecionado) {
							estado_atual = PRINCIPAL;
							encerrar = true;
						}
						else if (4 == selecionado) {
							encerrar = true;
							parar = true;
							exit(1);
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
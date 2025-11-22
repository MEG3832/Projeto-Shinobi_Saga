#include "Menu_Principal.h"
#include "Jogo.h"

Menu_Principal::Menu_Principal() :
	Menu(),
	texto_principal(),
	texto_selecaoFase(),
	texto_selecaoMultiplayer(),
	estado_atual(PRINCIPAL),
	titulo()
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

	titulo.setString("NOME DO JOGO");
	titulo.setCharacterSize(70);
	titulo.setFillColor(sf::Color(sf::Color::White));
	titulo.setOutlineColor(sf::Color::Black);
	titulo.setOutlineThickness(3);
	titulo.setPosition(GG->getCamera().getCenter().x - titulo.getLocalBounds().width / 2, GG->getCamera().getCenter().y - 160);
	titulo.setFont(fonte);

	sf::Text temp;

	temp.setCharacterSize(30);
	temp.setFillColor(sf::Color(sf::Color::White));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setFont(fonte);

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
	temp.setCharacterSize(30);
	temp.setFillColor(sf::Color(sf::Color::White));
	temp.setOutlineColor(sf::Color::Black);
	temp.setOutlineThickness(3);
	temp.setFont(fonte);

	temp.setString("Selecionar Fase");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25);
	texto_principal.push_back(temp);

	temp.setString("Carregar Jogo");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45);
	texto_principal.push_back(temp);

	temp.setString("Colocacao");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 2);
	texto_principal.push_back(temp);

	temp.setString("Sair");
	temp.setPosition(GG->getCamera().getCenter().x - temp.getLocalBounds().width / 2, GG->getCamera().getCenter().y + 25 + 45 * 3);
	texto_principal.push_back(temp);
}

void Menu_Principal::desenharTexto() {
	if (pGG) {
		titulo.setPosition(GG->getCamera().getCenter().x - titulo.getLocalBounds().width / 2, titulo.getPosition().y);
		pGG->desenharTexto(titulo);
	}
	else {
		std::cout << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
	}
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
	selecionado = 0;
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
				Menu::desenharTexto();
				GG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (0 == selecionado) {
							estado_atual = SELECAO_FASE;
							encerrar = true;
						}
						if (1 == selecionado) {
							carregar();
							encerrar = true;
							parar = true;
						}
						if (2 == selecionado) {
							pJog->setEstado(2);	// Corresponde ao estado MENU_COLOCACAO no jogo*/
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
	selecionado = 0;
	bool encerrar = false;
	while (!encerrar) {
		if (GG) {
			if (GE) {
				executa = false;
				GG->limpaJanela();
				GG->atualizaCamera(sf::Vector2f(GG->getCamera().getCenter().x + 1, GG->getCamera().getCenter().y));	// "Anda"
				GE->executarMenu(static_cast<Menu*>(this));	// Verifica teclas apertadas
				fundo.executar();	// Imprime as camadas
				Menu::desenharTexto();
				desenharTexto();
				GG->mostrarEntes();	// Display
				if (executa) {
					if (pJog) {
						if (0 == selecionado) {
							pJog->setEstado(3);	// No Jogo, 3 eh o estado da fase 1 
							encerrar = true;
							parar = true;
						}
						else if (1 == selecionado) {
							pJog->setEstado(4);	// No Jogo, 3 eh o estado da fase 2 
							encerrar = true;
							parar = true;
						}
						else if (2 == selecionado) {
							estado_atual = PRINCIPAL;
							encerrar = true;
						}
						else if (3 == selecionado) {
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

void Menu_Principal::carregar() {

	int fase = 0;
	bool multiplayer = false;

	/* Cria uma instancia de iftream (input file stream), usado para ler o arquivo no disco*/
	std::ifstream ifs("arquivo_fase.json");

	if (ifs.is_open()) {	// Verifica se estah aberto
		try {

			/* Faz o parse, ou seja, lê todos os dados do fluxo ifs, transformando-os em um objeto JSON na memoria*/
			nlohmann::json j = nlohmann::json::parse(ifs);
			ifs.close();	// Fecha o arquivo e para a leitura e analise

			std::cout << "Jogo carregado de: " << "arquivo_fase.json" << std::endl << std::endl;
			/* Acessar o valor associado a chave "fase_atual", transformando-a em um int*/
			try {
				fase = j.at("fase").get<int>();
				multiplayer = j.at("multiplayer").get<int>();

			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Chave 'fase' ausente." << e.what() << std::endl;
			}


			if (1 == fase) {
				Fases::FasePrimeira* pFase1 = nullptr;

				if (multiplayer) {
					pFase1 = new Fases::FasePrimeira(pJog1, pJog2);
				}
				else {
					pFase1 = new Fases::FasePrimeira(pJog1);
				}
				pJog->setMultiplayer(multiplayer);

				pFase1->carregar(j);

				pJog->setFase(pFase1, nullptr);

				pJog->setEstado(3);	// 3 indica o estado FASE1 do Jogo
			}
			else if (2 == fase) {
				Fases::FaseSegunda* pFase2 = nullptr;

				if (multiplayer) {
					pFase2 = new Fases::FaseSegunda(pJog1, pJog2);
				}
				else {
					pFase2 = new Fases::FaseSegunda(pJog1);
				}
				pJog->setMultiplayer(multiplayer);

				pFase2->carregar(j);

				pJog->setFase(nullptr, pFase2);

				pJog->setEstado(4);	// 4 indica o estado FASE2 do Jogo
			}

			Entidades::Entidade::limparBuffers();
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
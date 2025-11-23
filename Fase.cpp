#include "Fase.h"

namespace Fases
{
	Fase::Fase(Entidades::Personagens::Jogador* pJog1) :
		maxTengus(5),
		maxPlataf(8),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		GE(GE->getGerenciadorEventos()),
		pJog1(pJog1),
		pJog2(nullptr),
		pFundo(nullptr),
		fim_mapa(0),
		altura_chao(0.0),
		buffer_fase({}),
		menu_save_rank()
	{
		Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
									static_cast<Entidades::Personagens::Personagem*>(pJog1)); //coloca o jogador na lista de entidades
		lista_ents.incluir(pEnt);

		GC->setJogador1(pJog1);
		GC->setJogador2(nullptr);

		pFundo = new Parallax::Fundo(); //cria o fundo

		inicializarTexto();
		
		if (pJog1) {
			pJog1->restaurarVida();
		}
		else {
			std::cerr << "ERRO: nao eh possivel restaurar a vida do jogador 1 pois ele eh NULL" << std::endl;
		}

		if (pJog2) {
			pJog2->restaurarVida();
		}

	}

	Fase::Fase(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2) :
		pJog1(pJog1),
		pJog2(pJog2),
		maxTengus(5),
		maxPlataf(8),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		GE(GE->getGerenciadorEventos()),
		pFundo(nullptr),
		fim_mapa(0),
		altura_chao(0.0)
	{
		Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
									static_cast<Entidades::Personagens::Personagem*>(pJog1)); //coloca o jogador na lista de entidades
		Entidades::Entidade* pEnt2 = static_cast<Entidades::Entidade*>(
									 static_cast<Entidades::Personagens::Personagem*>(pJog2));
		lista_ents.incluir(pEnt);
		lista_ents.incluir(pEnt2);

		pFundo = new Parallax::Fundo(); //cria o fundo

		inicializarTexto();
	}

	Fase::~Fase()
	{
		//retiramos os jogadores da lista para que eles não sejam destruídos quando a fase acabar...
		if (pJog1) {
			lista_ents.remover(static_cast<Entidades::Entidade*>(
							   static_cast<Entidades::Personagens::Personagem*>(pJog1)));
		}
		if (pJog2) {
			lista_ents.remover(static_cast<Entidades::Entidade*>(
							   static_cast<Entidades::Personagens::Personagem*>(pJog2)));
		}

		lista_ents.limpar();
		if (GC) {
			GC->limparListas();
			GC = nullptr;
		}
		if (pFundo) {
			delete pFundo;
			pFundo = nullptr;
		}

		menu_save_rank.setSeguir(true);

		// não deletamos o GC aqui, pois ele é Singleton usado pelo Jogo inteiro.
		//A lista de entidades já é limpada ao ser destruída (lista_ents é da classe Lista_Entidades, q possui uma Lista parametrizada com Entidades)
	}

	void Fase::executar()
	{
			pGG->limpaJanela();

			if (GE) {
				GE->executar();
			}
			else {
				std::cerr << "Nao eh possivel executar o Gerenciador de Eventos pois ele eh NULL" << std::endl;
			}

			if (GC) {
				GC->executar();
			}
			else {
				std::cerr << "Nao eh possivel executar o Gerenciador de Colisoes pois ele eh NULL" << std::endl;
			}

			lista_ents.percorrer();

			lista_ents.aplicarGravidade();

			if (pJog1) {
				pGG->atualizaCamera(pJog1->getPos());

				if (pJog1->getCorpo()) {
					if (!pJog1->podeSeguirPorMorte()) {
						menu_save_rank.setSeguir(false);
						menu_save_rank.executar();
					}
					if (pJog1->getCorpo()->getPosition().x >= fim_mapa) {
						menu_save_rank.executar();
					}
				}

			}

			if (pJog2) {
				if (pJog2->getCorpo()) {
					if (!pJog2->podeSeguirPorMorte()) {
						menu_save_rank.setSeguir(false);
						menu_save_rank.executar();
					}
					if (pJog2->getCorpo()->getPosition().x >= fim_mapa) {
						menu_save_rank.executar();
					}
				}

			}
			
			if (pFundo)
				pFundo->executar();

			lista_ents.desenharEntidades();

			desenharTexto();

			pGG->mostrarEntes();
	}

	void Fase::criarTengus()
	{

		const int min_tengus = 3;

		int qnt_tengus = (rand() % (maxTengus - min_tengus + 1)) + min_tengus; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_tengus; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(pJog1,pJog2); //temos que passar o endereço do jogador aqui...

			if (pTengu)
			{
				int correcao = 0;

				do {
					int posX = (1000 + i * 4000 + i * rand() % 1000 + correcao) % fim_mapa;

					int posY = 0;	// Faz com que os inimigos em uma certa distancia se
					if (posX > 500) {
						posY = 50;
					}
					else {
						posY = pGG->getWindow()->getSize().y - altura_chao - pTengu->getCorpo()->getSize().y;
					}

					if (pTengu->getCorpo()) {
						pTengu->getCorpo()->setPosition(posX, posY);
					}
					if (pTengu->getHitBox()) {
						pTengu->getHitBox()->setPosition(pTengu->getCorpo()->getPosition().x + (pTengu->getCorpo()->getSize().x / 2 - pTengu->getHitBox()->getSize().x / 2),
							pTengu->getCorpo()->getPosition().y);
					}

					correcao += 20;
				} while (GC->verificaColisaoEnteObstacs(pTengu) || GC->verificaColisaoEnteInimgs(pTengu));

				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pTengu));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Personagens::Personagem*>(
											static_cast<Entidades::Personagens::Inimigo*>(pTengu)));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar o Tengu!" << std::endl;

		}

	}

	void Fase::criarPlataformas(int id)
	{

		const int min_plataf = 3;

		int qnt_plataf = (rand() % (maxPlataf - min_plataf + 1)) + min_plataf; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_plataf; i++)
		{
			Entidades::Obstaculos::Plataforma* pPlataf;
			pPlataf = new Entidades::Obstaculos::Plataforma(id);

			if (pPlataf)
			{ 
				int correcao = 0;

				do {
					int posX = (300 + i * 4500 + i * rand() % 1500 + correcao) % fim_mapa;
					int posY = ALTURA_TELA - altura_chao - pPlataf->getTam().y -
						(rand() % 10 + 160);

					if (pPlataf->getCorpo()) {
						pPlataf->getCorpo()->setPosition(posX, posY);
					}
					if (pPlataf->getHitBox()) {
						pPlataf->getHitBox()->setPosition(pPlataf->getCorpo()->getPosition().x + (pPlataf->getCorpo()->getSize().x / 2 - pPlataf->getHitBox()->getSize().x / 2),
							pPlataf->getCorpo()->getPosition().y);
					}

					correcao += 20;
				} while (GC->verificaColisaoEnteObstacs(pPlataf) || GC->verificaColisaoEnteInimgs(pPlataf));

				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pPlataf));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Obstaculos::Obstaculo*>(pPlataf));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar a plataforma!" << std::endl;

		}

	}

	void Fase::carregarTengus(const nlohmann::json& j) {
		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_tengus = j.at("Tengus");

			for (const auto& tengu_json : lista_tengus) {
				Entidades::Personagens::Inimigo* pTengu;
				pTengu = new Entidades::Personagens::Tengu(pJog1);

				pTengu->carregar(tengu_json);

				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pTengu));
				Entidades::Entidade* pEnt  = (static_cast<Entidades::Entidade*>(
											  static_cast<Entidades::Personagens::Personagem*>(
											  static_cast<Entidades::Personagens::Inimigo*>(pTengu))));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Tengus' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}

	void Fase::carregarPlataf(const nlohmann::json& j, int id) {
		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_plataformas = j.at("Plataformas");

			for (const auto& plataforma_json : lista_plataformas) {
				Entidades::Obstaculos::Plataforma* pPlatf;
				pPlatf = new Entidades::Obstaculos::Plataforma(id);

				pPlatf->carregar(plataforma_json);

				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pPlatf));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Obstaculos::Obstaculo*>(pPlatf));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Plataformas' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}

	}

	// Esta funcionando pra um jogador
	void Fase::carregarJogadores(const nlohmann::json& j) {
		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_jogadores = j.at("Jogadores");

			const nlohmann::json& jogador_json = lista_jogadores.at(0);
			pJog1->carregar(jogador_json);
			GC->setJogador1(pJog1);
			GE->setJogador1(pJog1);
			Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
										static_cast<Entidades::Personagens::Personagem*>(pJog1));
			lista_ents.incluir(pEnt);

			if (pJog2) {
				const nlohmann::json& jogador_json = lista_jogadores.at(1);
				pJog2->carregar(jogador_json);
				GC->setJogador2(pJog2);
				GE->setJogador2(pJog2);
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Personagens::Personagem*>(pJog2));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Jogadores' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}

	void Fase::carregar(const nlohmann::json& j, int id) {

		carregarJogadores(j);
		carregarTengus(j);
		carregarPlataf(j, id);

	}

	void Fase::inicializarTexto() {

		fonte.loadFromFile("Fonte/superstar_memesbruh03.ttf");

		sf::Text temp;
		temp.setCharacterSize(25);
		temp.setFillColor(sf::Color(sf::Color::White));
		temp.setOutlineColor(sf::Color::Black);
		temp.setOutlineThickness(3);
		temp.setFont(fonte);

		if (pJog1) {
			temp.setFillColor(sf::Color::White);
			temp.setString("Jogador 1");
			temp.setPosition(pGG->getCamera().getCenter().x - 350, 25);
			texto_Jog1.push_back(temp);

			temp.setFillColor(sf::Color(99, 162, 121));
			temp.setString(std::to_string(pJog1->getVida()));
			temp.setPosition(pGG->getCamera().getCenter().x - 350, 25 + 30);
			texto_Jog1.push_back(temp);

			temp.setFillColor(sf::Color::White);
			temp.setString(std::to_string(pJog1->getPontuacao()));
			temp.setPosition(pGG->getCamera().getCenter().x - 350, 25 + 25 + 30);
			texto_Jog1.push_back(temp);
		}

		if (pJog2) {
			temp.setFillColor(sf::Color::White);
			temp.setString("Jogador 2");
			temp.setPosition(pGG->getCamera().getCenter().x - 225, 25);
			texto_Jog2.push_back(temp);

			temp.setFillColor(sf::Color(99, 162, 121));
			temp.setString(std::to_string(pJog2->getVida()));
			temp.setPosition(pGG->getCamera().getCenter().x - 225, 25 + 30);
			texto_Jog2.push_back(temp);

			temp.setFillColor(sf::Color::White);
			temp.setString(std::to_string(pJog2->getPontuacao()));
			temp.setPosition(pGG->getCamera().getCenter().x - 225, 25 + 25 + 30);
			texto_Jog2.push_back(temp);
		}
	}

	void Fase::desenharTexto() {
		if (pGG) {
			if (pJog1) {
				texto_Jog1[1].setString(std::to_string(pJog1->getVida()));
				texto_Jog1[2].setString(std::to_string(pJog1->getPontuacao()));

				for (int i = 0; i < (int)texto_Jog1.size(); i++) {
					texto_Jog1[i].setPosition(pGG->getCamera().getCenter().x - 350, texto_Jog1[i].getPosition().y);
					pGG->desenharTexto(texto_Jog1[i]);
				}
			}

			if (pJog2) {
				texto_Jog2[1].setString(std::to_string(pJog2->getVida()));
				texto_Jog2[2].setString(std::to_string(pJog2->getPontuacao()));

				for (int i = 0; i < (int)texto_Jog2.size(); i++) {
					texto_Jog2[i].setPosition(pGG->getCamera().getCenter().x - 225, texto_Jog2[i].getPosition().y);
					pGG->desenharTexto(texto_Jog2[i]);
				}
			}
		}
		else {
			std::cout << "ERRO: Nao eh possivel desenhar o texo pois o Gerenciador Grafico eh NULL" << std::endl;
		}
	}

}

#include "Fase.h"

namespace Fases
{
	Fase::Fase() :
		maxTengus(5),
		maxPlataf(8),
		qnt_tengus(0),
		qnt_plataf(0),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		GE(GE->getGerenciadorEventos()),
		pJog(nullptr),
		pFundo(nullptr),
		fim_mapa(0),
		altura_chao(0.0),
		buffer_fase({})
	{
		pJog = new Entidades::Personagens::Jogador(); //cria o jogador

		Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pJog); //coloca o jogador na lista de entidades
		lista_ents.incluir(pEnt);

		GC->setJogador(pJog); //por enquanto, só o jogador é setado no gerenc. de colisões
		GC->setAlturaChao(80);	// Determinado olhando a sprite do fundo

		pFundo = new Parallax::Fundo(); //cria o fundo

	}

	Fase::~Fase()
	{
		if (GC)
		{
			delete(GC);
			GC = nullptr;
		}
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

			if (pJog) {
				pGG->atualizaCamera(pJog->getPos());
			}
			
			if (pFundo)
				pFundo->executar();

			lista_ents.desenharEntidades();

			//teste (o ideal eh colocar uma parede invisivel)
			if (pJog->getCorpo()->getPosition().x >= fim_mapa) {
				std::cout << "fim!!" << std::endl;
			}

			pGG->mostrarEntes();
	}

	void Fase::criarTengus()
	{

		const int min_tengus = 3;

		qnt_tengus = (rand() % (maxTengus - min_tengus + 1)) + min_tengus; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_tengus; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(pJog); //temos que passar o endereço do jogador aqui...

			if (pTengu)
			{
				int correcao = 0;

				do {
					int posX = (1000 + i * 4000 + i * rand() % 1000 + correcao) % fim_mapa;
					int posY = pGG->getWindow()->getSize().y - altura_chao - pTengu->getCorpo()->getSize().y;

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

	void Fase::criarPlataformas()
	{

		const int min_plataf = 3;

		qnt_plataf = (rand() % (maxPlataf - min_plataf + 1)) + min_plataf; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_plataf; i++)
		{
			Entidades::Obstaculos::Plataforma* pPlataf;
			pPlataf = new Entidades::Obstaculos::Plataforma();

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

	void Fase::carregarTengus() {
		for (int i = 0; i < qnt_tengus; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(pJog); //temos que passar o endereço do jogador aqui...

			if (pTengu)
			{
				int correcao = 0;

				do {
					int posX = (1000 + i * 4000 + i * rand() % 1000 + correcao) % fim_mapa;
					int posY = pGG->getWindow()->getSize().y - altura_chao - pTengu->getCorpo()->getSize().y;

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

	void Fase::carregarPlataf(const nlohmann::json& j) {
		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_plataformas = j.at("Plataformas");

			for (const auto& plataforma_json : lista_plataformas) {
				Entidades::Obstaculos::Plataforma* pPlataf;
				pPlataf = new Entidades::Obstaculos::Plataforma();

				float posX = plataforma_json.at("posX").get<float>();
				float posY = plataforma_json.at("posY").get<float>();

				if (pPlataf->getCorpo()) {
					pPlataf->getCorpo()->setPosition(posX, posY);
				}
				else {
					std::cerr << "ERRO: Nao eh possivel setar a posicao da plataforma pois seu corpo eh NULL" << std::endl;
				}

				if (pPlataf->getHitBox()) {
					pPlataf->getHitBox()->setPosition(pPlataf->getCorpo()->getPosition().x + (pPlataf->getCorpo()->getSize().x / 2 - pPlataf->getHitBox()->getSize().x / 2),
						pPlataf->getCorpo()->getPosition().y);
				}
				else {
					std::cerr << "ERRO: Nao eh possivel setar a posicao da plataforma pois seu hit box eh NULL" << std::endl;
				}


				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pPlataf));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Obstaculos::Obstaculo*>(pPlataf));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array Plataformas' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}

	}

	void Fase::salvarDataBuffer() {
		buffer_fase["qnt_tengus"] = qnt_tengus;
		buffer_fase["qnt_plataf"] = qnt_plataf;
	}

	void Fase::carregar(const nlohmann::json& j) {
		qnt_tengus = j.at("qnt_tengus").get<int>();
		qnt_plataf = j.at("qnt_plataf").get<int>();

		//carregarTengus();
		carregarPlataf(j);
	}

	Entidades::Personagens::Jogador* Fase::getJogador() {
		return pJog;
	}


}

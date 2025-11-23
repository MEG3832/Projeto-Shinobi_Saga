#include "FasePrimeira.h"
#include "Samurai_Inimigo.h"
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Redemoinho.h"

namespace Fases
{

	FasePrimeira::FasePrimeira(Entidades::Personagens::Jogador* pJog1) :
		Fase(pJog1),
		maxSamurais(8),
		maxRedemoinhos(8)
	{
		altura_chao = 80.0;	// Medi olhando e testando
		GC->setAlturaChao(altura_chao);	// Determinado olhando a sprite do fundo

		fim_mapa = 10000;

		criarCenario();

		pJog1->getCorpo()->setPosition(100.0f, ALTURA_TELA - altura_chao - pJog1->getTam().y);
		pJog1->getHitBox()->setPosition(pJog1->getCorpo()->getPosition().x + (pJog1->getCorpo()->getSize().x / 2 - pJog1->getHitBox()->getSize().x / 2),
										pJog1->getCorpo()->getPosition().y);

		criarObstaculos();
		criarInimigos();
	}

	FasePrimeira::FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2) :
		Fase(pJog1,pJog2),
		maxSamurais(8),
		maxRedemoinhos(8)
	{
		altura_chao = 80.0;	// Medi olhando e testando
		GC->setAlturaChao(altura_chao);	// Determinado olhando a sprite do fundo

		fim_mapa = 10000;

		criarCenario();

		//para o jogador 1
		pJog1->getCorpo()->setPosition(100.0f, ALTURA_TELA - altura_chao - pJog1->getTam().y);
		pJog1->getHitBox()->setPosition(pJog1->getCorpo()->getPosition().x + (pJog1->getCorpo()->getSize().x / 2 - pJog1->getHitBox()->getSize().x / 2),
										pJog1->getCorpo()->getPosition().y);

		//para o jogador 2
		pJog2->getCorpo()->setPosition(60.0f, ALTURA_TELA - altura_chao - pJog2->getTam().y);
		pJog2->getHitBox()->setPosition(pJog2->getCorpo()->getPosition().x + (pJog2->getCorpo()->getSize().x / 2 - pJog2->getHitBox()->getSize().x / 2),
										pJog2->getCorpo()->getPosition().y);

		criarObstaculos();
		criarInimigos();
	}

	FasePrimeira::~FasePrimeira()
	{
		if (pFundo) {
			delete pFundo;
			pFundo = nullptr;
		}
	}

	void FasePrimeira::criarCenario() {
		// pFundo foi criado no construtor de Fase.
		// Apenas adicionamos as camadas.

		// (tam, vel, caminhoTextura)

		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada1.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada2.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.00000000001f, "Imagens/JapanVillage/Camada3.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000000001f, "Imagens/JapanVillage/Camada4.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000000001f, "Imagens/JapanVillage/Camada5.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.05f, "Imagens/JapanVillage/Camada6.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada7.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.3f, "Imagens/JapanVillage/Camada8.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.05f, "Imagens/JapanVillage/Camada9.png");
	}

	void FasePrimeira::criarInimigos()
	{
		criarTengus(); // está na classe base, já que a fase 2 também terá Tengus.

		criarSamurais();
	}

	void FasePrimeira::criarSamurais()
	{

		const int min_samurais = 3;
		
		//int qnt_samurais = (rand() % (maxSamurais - min_samurais + 1)) + min_samurais; //gera valor entre minimo e maximo definido
		int qnt_samurais = 0;
		for (int i = 0; i < qnt_samurais; i++)
		{
			//calcula uma resistência aleatória (float) entre 1.0 e 2.0
			float min_res = 1.0f; //o samurai vai receber um dano normal
			float max_res = 2.0f; //o samurai vai receber um dano pela metade.
			float rand_percent = (float)rand() / (float)RAND_MAX; //essa divisão resulta em um valor no intervalo [0.0 , 1.0]
			float resistencia_aleatoria = min_res + rand_percent * (max_res - min_res);

			Entidades::Personagens::Samurai_Inimigo* pSam;
			pSam = new Entidades::Personagens::Samurai_Inimigo(pJog1, pJog2, resistencia_aleatoria); 

			if (pSam)
			{
				int correcao = 0;
				do {
					int posX = (400 + i * 3500 + i * rand() % 400 + correcao) % fim_mapa;
					float posY = pGG->getWindow()->getSize().y - altura_chao - pSam->getCorpo()->getSize().y;

					if (pSam->getCorpo()) {
						pSam->getCorpo()->setPosition(posX, posY);
					}
					if (pSam->getHitBox()) {
						pSam->getHitBox()->setPosition(pSam->getCorpo()->getPosition().x + (pSam->getCorpo()->getSize().x / 2 - pSam->getHitBox()->getSize().x / 2),
							pSam->getCorpo()->getPosition().y);
					}
					correcao += 20;
				} while(GC->verificaColisaoEnteObstacs(pSam) || GC->verificaColisaoEnteInimgs(pSam));

				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pSam));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Personagens::Personagem*>(
											static_cast<Entidades::Personagens::Inimigo*>(pSam)));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar o Samurai Inimigo!" << std::endl;

		}
	}

	void FasePrimeira::criarObstaculos()
	{
		criarPlataformas(1);	// Identifica que a textura usada eh da primeira fase

		criarRedemoinhos();
	}

	void FasePrimeira::criarRedemoinhos()
	{

		const int min_red = 3;

		//int qnt_redemoinhos = (rand() % (maxRedemoinhos - min_red + 1)) + min_red; //gera valor entre minimo e maximo definido
		int qnt_redemoinhos = 0;

		for (int i = 0; i < qnt_redemoinhos; i++)
		{
			Entidades::Obstaculos::Redemoinho* pRed;
			pRed = new Entidades::Obstaculos::Redemoinho();

			if (pRed)
			{
				int correcao = 0;
				do {
					int posX = (2500 + i * 5000 + i * rand() % 800 + correcao) % fim_mapa;
					float posY = ALTURA_TELA - altura_chao - pRed->getTam().y;
					if (pRed->getCorpo()) {
						pRed->getCorpo()->setPosition(posX, posY);
					}
					if (pRed->getHitBox()) {
						pRed->getHitBox()->setPosition(pRed->getCorpo()->getPosition().x + (pRed->getCorpo()->getSize().x / 2 - pRed->getHitBox()->getSize().x / 2),
							pRed->getCorpo()->getPosition().y);
					}

					correcao += 20;
				} while (GC->verificaColisaoEnteObstacs(pRed) || GC->verificaColisaoEnteInimgs(pRed));


				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pRed));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Obstaculos::Obstaculo*>(pRed));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar o redemoinho!" << std::endl;

		}
	}

	void FasePrimeira::carregarSamurais(const nlohmann::json& j) {
		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_samurais = j.at("Samurais");

			for (const auto& samurai_json : lista_samurais) {
				Entidades::Personagens::Samurai_Inimigo* pSamurai;

				float min_res = 1.0f; //o samurai vai receber um dano normal
				float max_res = 2.0f; //o samurai vai receber um dano pela metade.
				float rand_percent = (float)rand() / (float)RAND_MAX; //essa divisão resulta em um valor no intervalo [0.0 , 1.0]
				float resistencia_aleatoria = min_res + rand_percent * (max_res - min_res);

				pSamurai = new Entidades::Personagens::Samurai_Inimigo(pJog1, pJog2, resistencia_aleatoria);

				pSamurai->carregar(samurai_json);

				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pSamurai));
				Entidades::Entidade* pEnt = (static_cast<Entidades::Entidade*>(
											 static_cast<Entidades::Personagens::Personagem*>(
											 static_cast<Entidades::Personagens::Inimigo*>(pSamurai))));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Samurais' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}

	void FasePrimeira::carregarRedemoinhos(const nlohmann::json& j) {

		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_redemoinhos = j.at("Redemoinhos");

			for (const auto& redemoinho_json : lista_redemoinhos) {
				Entidades::Obstaculos::Redemoinho* pRed;
				pRed = new Entidades::Obstaculos::Redemoinho();

				pRed->carregar(redemoinho_json);

				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pRed));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Obstaculos::Obstaculo*>(pRed));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Redemoinhos' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}

	}

	void FasePrimeira::salvarDataBuffer() {

		buffer_fase["fase"] = 1;
		if (pJog2) {
			buffer_fase["multiplayer"] = true;
		}
		else {
			buffer_fase["multiplayer"] = false;
		}
	}

	void FasePrimeira::salvar() {

		salvarDataBuffer();

		std::ofstream arquivo_fase("arquivo_fase.json");

		lista_ents.salvar();
		buffer_fase["Plataformas"] = Entidades::Entidade::getArrayPlataformas();
		buffer_fase["Redemoinhos"] = Entidades::Entidade::getArrayRedemoinhos();
		buffer_fase["Tengus"] = Entidades::Entidade::getArrayTengus();
		buffer_fase["Samurais"] = Entidades::Entidade::getArraySamurais();
		buffer_fase["Jogadores"] = Entidades::Entidade::getArrayJogadores();

		if (arquivo_fase.is_open()) {	// Verifica se o arquivo foi aberto
			/* Escreve tudo no arquivo (serializa), com uma indentação de 4 espaços pra tornar mais legível*/
			arquivo_fase << buffer_fase.dump(4);
			arquivo_fase.close();	// Fecha o arquivo e para a escrita

			std::cout << "Fase 1 salva em : " << "arquivo_fase.json" << std::endl;
		}
		else {
			std::cerr << "ERRO: Nao foi possivel abrir o arquivo da fase 1 para salvar." << std::endl;
		}
	}

	void FasePrimeira::carregar(const nlohmann::json& j) {
		try {
			lista_ents.remover(pJog1);
			if (pJog2) {
				lista_ents.remover(pJog2);
			}
			lista_ents.limpar();
			GC->limparListas();

			Fase::carregar(j, 1);

			carregarSamurais(j);
			carregarRedemoinhos(j);
		}

		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: Alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}
}
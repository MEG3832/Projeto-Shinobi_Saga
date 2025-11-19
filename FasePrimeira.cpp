#include "FasePrimeira.h"
#include "Samurai_Inimigo.h"
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Redemoinho.h"

namespace Fases
{

	FasePrimeira::FasePrimeira() :
		Fase(),
		maxSamurais(8),
		maxRedemoinhos(8),
		qnt_samurais(0),
		qnt_redemoinhos(0)
	{
		altura_chao = 80.0;	// Medi olhando e testando

		fim_mapa = 10000;

		criarCenario();

		pJog->getCorpo()->setPosition(0.0f, ALTURA_TELA - altura_chao - pJog->getTam().y);
		pJog->getHitBox()->setPosition(pJog->getCorpo()->getPosition().x + (pJog->getCorpo()->getSize().x / 2 - pJog->getHitBox()->getSize().x / 2),
										pJog->getCorpo()->getPosition().y);

		criarObstaculos();
		criarInimigos();
	}

	FasePrimeira::~FasePrimeira()
	{

	}

	void FasePrimeira::criarCenario() {
		// pFundo foi criado no construtor de Fase.
		// Apenas adicionamos as camadas.

		// Exemplo de camadas para Fase 1:
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
		
		qnt_samurais = (rand() % (maxSamurais - min_samurais + 1)) + min_samurais; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_samurais; i++)
		{
			//calcula uma resistência aleatória (float) entre 1.0 e 2.0
			float min_res = 1.0f; //o samurai vai receber um dano normal
			float max_res = 2.0f; //o samurai vai receber um dano pela metade.
			float rand_percent = (float)rand() / (float)RAND_MAX; //essa divisão resulta em um valor no intervalo [0.0 , 1.0]
			float resistencia_aleatoria = min_res + rand_percent * (max_res - min_res);

			Entidades::Personagens::Samurai_Inimigo* pSam;
			pSam = new Entidades::Personagens::Samurai_Inimigo(pJog, resistencia_aleatoria); 

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
		criarPlataformas();

		criarRedemoinhos();
	}

	void FasePrimeira::criarRedemoinhos()
	{

		const int min_red = 3;

		qnt_redemoinhos = (rand() % (maxRedemoinhos - min_red + 1)) + min_red; //gera valor entre minimo e maximo definido


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

	void FasePrimeira::carregarSamurais() {
		for (int i = 0; i < qnt_samurais; i++)
		{
			//calcula uma resistência aleatória (float) entre 1.0 e 2.0
			float min_res = 1.0f; //o samurai vai receber um dano normal
			float max_res = 2.0f; //o samurai vai receber um dano pela metade.
			float rand_percent = (float)rand() / (float)RAND_MAX; //essa divisão resulta em um valor no intervalo [0.0 , 1.0]
			float resistencia_aleatoria = min_res + rand_percent * (max_res - min_res);

			Entidades::Personagens::Samurai_Inimigo* pSam;
			pSam = new Entidades::Personagens::Samurai_Inimigo(pJog, resistencia_aleatoria);

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
				} while (GC->verificaColisaoEnteObstacs(pSam) || GC->verificaColisaoEnteInimgs(pSam));

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

		Fase::salvarDataBuffer();

		buffer_fase["fase"] = 1;
		buffer_fase["qnt_samurais"] = qnt_samurais;
		buffer_fase["qnt_redemoinhos"] = qnt_redemoinhos;
	}

	void FasePrimeira::salvar() {

		salvarDataBuffer();

		std::ofstream arquivo_fase("arquivo_fase.json");

		lista_ents.salvar();
		buffer_fase["Plataformas"] = Entidades::Entidade::getArrayPlataformas();
		buffer_fase["Redemoinhos"] = Entidades::Entidade::getArrayRedemoinhos();
		buffer_fase["Tengus"] = Entidades::Entidade::getArrayTengus();

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
			lista_ents.limpar();
			GC->limparListas();

			pJog = new Entidades::Personagens::Jogador(); //cria o jogador
			pJog->getCorpo()->setPosition(0.0, ALTURA_TELA - pJog->getCorpo()->getSize().y - altura_chao);

			Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pJog); //coloca o jogador na lista de entidades
			lista_ents.incluir(pEnt);

			GC->setJogador(pJog); //por enquanto, só o jogador é setado no gerenc. de colisões
			GE->setJogador(pJog); 

			Fase::carregar(j);

			qnt_samurais = j.at("qnt_samurais").get<int>();
			qnt_redemoinhos = j.at("qnt_redemoinhos").get<int>();

			//carregarSamurais();
			carregarRedemoinhos(j);
		}

		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: Alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}
}
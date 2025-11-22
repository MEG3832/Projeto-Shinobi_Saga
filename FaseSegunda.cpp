#include "FaseSegunda.h"
#include "Kitsune.h"
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Armadilha_de_urso.h"
#include "Projetil.h"

namespace Fases
{

	FaseSegunda::FaseSegunda(Entidades::Personagens::Jogador* pJog1) :
		Fase(pJog1),
		maxKitsunes(8),
		maxArmadilhas(8)
	{
		altura_chao = 50.0;	// Medi olhando e testando

		fim_mapa = 10000;

		criarCenario();

		GC->setAlturaChao(altura_chao);	// Determinado olhando a sprite do fundo

		pJog1->getCorpo()->setPosition(0.0f, ALTURA_TELA - altura_chao - pJog1->getTam().y);
		pJog1->getHitBox()->setPosition(pJog1->getCorpo()->getPosition().x + (pJog1->getCorpo()->getSize().x / 2 - pJog1->getHitBox()->getSize().x / 2),
										pJog1->getCorpo()->getPosition().y);

		criarObstaculos();
		criarInimigos();
	}

	FaseSegunda::FaseSegunda(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2) :
		Fase(pJog1, pJog2),
		maxKitsunes(8),
		maxArmadilhas(8)
	{
		altura_chao = 50.0;	// Medi olhando e testando
		GC->setAlturaChao(altura_chao);	// Determinado olhando a sprite do fundo

		fim_mapa = 10000;

		criarCenario();

		pJog1->getCorpo()->setPosition(0.0f, ALTURA_TELA - altura_chao - pJog1->getTam().y);
		pJog1->getHitBox()->setPosition(pJog1->getCorpo()->getPosition().x + (pJog1->getCorpo()->getSize().x / 2 - pJog1->getHitBox()->getSize().x / 2),
										pJog1->getCorpo()->getPosition().y);

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

	FaseSegunda::~FaseSegunda()
	{
		if (pFundo) {
			delete pFundo;
			pFundo = nullptr;
		}
	}

	void FaseSegunda::criarCenario() {
		// pFundo foi criado no construtor de Fase.
		// Apenas adicionamos as camadas.

		// (tam, vel, caminhoTextura)

		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000000001f, "Imagens/DarkForest/Camada1.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000000001f, "Imagens/DarkForest/Camada2.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.5f, "Imagens/DarkForest/Camada3.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.3f, "Imagens/DarkForest/Chao.png");

	}

	void FaseSegunda::criarInimigos()
	{
		criarTengus(); // está na classe base, já que a fase 2 também terá Tengus.

		criarKitsunes();
	}

	void FaseSegunda::criarKitsunes()
	{
		const int min_kitsunes = 3;

		//int qnt_inim = (rand() % (maxKitsunes - min_kitsunes + 1)) + min_kitsunes; //gera valor entre minimo e maximo definido
		int qnt_inim = 0;
		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Kitsune* pKits;
			pKits = new Entidades::Personagens::Kitsune(pJog1,pJog2);

			if (pKits)
			{
				//criamos o projétil da kitsune aqui!
				criarProjetil(pKits);

				int correcao = 0;
				do {
					int posX = (400 + i * 3500 + i * rand() % 400 + correcao) % fim_mapa;
					float posY = pGG->getWindow()->getSize().y - altura_chao - pKits->getCorpo()->getSize().y;

					if (pKits->getCorpo()) {
						pKits->getCorpo()->setPosition(posX, posY);
					}
					if (pKits->getHitBox()) {
						pKits->getHitBox()->setPosition(pKits->getCorpo()->getPosition().x + (pKits->getCorpo()->getSize().x / 2 - pKits->getHitBox()->getSize().x / 2),
														pKits->getCorpo()->getPosition().y);
					}
					correcao += 20;
				} while (GC->verificaColisaoEnteObstacs(pKits) || GC->verificaColisaoEnteInimgs(pKits));

				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pKits));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Personagens::Personagem*>(
											static_cast<Entidades::Personagens::Inimigo*>(pKits)));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar a Kitsune!" << std::endl;

		}
	}

	
	void FaseSegunda::criarProjetil(Entidades::Personagens::Kitsune* pKits)
	{
		Entidades::Projetil* pProj;

		pProj = new Entidades::Projetil(pKits);

		if (pProj)
		{
			pKits->setProjetil(pProj);
			GC->incluirProjetil(pProj);

			Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*> (pProj);

			lista_ents.incluir(pEnt);
		}

		else
			std::cout << "Não foi possível alocar o Projetil!" << std::endl;
		

	}


	void FaseSegunda::criarObstaculos()
	{
		criarPlataformas(2); // identifica que a textura usada eh a da segunda fase

		criarArmadilhas();
	}

	void FaseSegunda::criarArmadilhas()
	{

		const int min_armad = 3;

		//int qnt_armad = (rand() % (maxArmadilhas - min_armad + 1)) + min_armad; //gera valor entre minimo e maximo definido
		int qnt_armad = 0;

		for (int i = 0; i < qnt_armad; i++)
		{
			Entidades::Obstaculos::Armadilha_de_urso* pArmad;
			pArmad = new Entidades::Obstaculos::Armadilha_de_urso();

			if (pArmad)
			{
				int correcao = 0;
				do {
					int posX = (2500 + i * 5000 + i * rand() % 800 + correcao) % fim_mapa;
					float posY = ALTURA_TELA - 30 - pArmad->getTam().y;
					if (pArmad->getCorpo()) {
						pArmad->getCorpo()->setPosition(posX, posY);
					}
					if (pArmad->getHitBox()) {
						pArmad->getHitBox()->setPosition(pArmad->getCorpo()->getPosition().x + (pArmad->getCorpo()->getSize().x / 2 - pArmad->getHitBox()->getSize().x / 2),
														 pArmad->getCorpo()->getPosition().y);
					}

					correcao += 20;
				} while (GC->verificaColisaoEnteObstacs(pArmad) || GC->verificaColisaoEnteInimgs(pArmad));


				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pArmad));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Obstaculos::Obstaculo*>(pArmad));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar a armadilha!" << std::endl;

		}
	}

	Entidades::Projetil* FaseSegunda::carregarProjetil(const nlohmann::json& j, Entidades::Personagens::Kitsune* pKits, int i) {
		try {
			if (pKits) {
				// Obtém a referência para o array completo de "plataformas"
				const nlohmann::json& lista_projeteis = j.at("Projeteis");
				const nlohmann::json& projetil_json = lista_projeteis.at(i);

				Entidades::Projetil* pProj;
				pProj = new Entidades::Projetil(pKits);

				pProj->carregar(projetil_json);

				GC->incluirProjetil(pProj);
				Entidades::Entidade* pEnt = (static_cast<Entidades::Entidade*>(pProj));
				lista_ents.incluir(pEnt);

				return pProj;
			}
			else {
				std::cerr << "ERRO: Nao eh possivel carregar o projetil pois sua kitsune associada eh NULL" << std::endl;
			}
		}
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Projeteis' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}

		return nullptr;
	}

	void FaseSegunda::carregarKitsunes(const nlohmann::json& j) {
		try {
			int i = 0;

			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_kitsunes = j.at("Kitsunes");

			for (const auto& kitsune_json : lista_kitsunes) {
				Entidades::Personagens::Kitsune* pKits;
				pKits = new Entidades::Personagens::Kitsune(pJog1);

				pKits->carregar(kitsune_json);

				pKits->setProjetil(carregarProjetil(j, pKits, i++));

				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pKits));
				Entidades::Entidade* pEnt = (static_cast<Entidades::Entidade*>(
											 static_cast<Entidades::Personagens::Personagem*>(
						static_cast<Entidades::Personagens::Inimigo*>(pKits))));
				lista_ents.incluir(pEnt);
			}
		}
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Kitsunes' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}

	void FaseSegunda::carregarArmadilhas(const nlohmann::json& j) {
		try {
			// Obtém a referência para o array completo de "plataformas"
			const nlohmann::json& lista_armadilhas = j.at("Armadilhas_de_urso");

			for (const auto& armadilhas_json : lista_armadilhas) {
				Entidades::Obstaculos::Armadilha_de_urso* pArmad;
				pArmad = new Entidades::Obstaculos::Armadilha_de_urso();

				pArmad->carregar(armadilhas_json);

				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pArmad));
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Obstaculos::Obstaculo*>(pArmad));
				lista_ents.incluir(pEnt);
			}
		}
		/* A funcao .what() explica de forma mais detalhada e especifica onde o erro e aconteceu e o que eh*/
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: O array 'Armadilhas_de_urso' ou alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}

	void FaseSegunda::salvar() {
		salvarDataBuffer();

		std::ofstream arquivo_fase("arquivo_fase.json");

		lista_ents.salvar();
		buffer_fase["Plataformas"] = Entidades::Entidade::getArrayPlataformas();
		buffer_fase["Armadilhas_de_urso"] = Entidades::Entidade::getArrayArmadilhas();
		buffer_fase["Tengus"] = Entidades::Entidade::getArrayTengus();
		buffer_fase["Kitsunes"] = Entidades::Entidade::getArrayKitsunes();
		buffer_fase["Projeteis"] = Entidades::Entidade::getArrayProjeteis();
		buffer_fase["Jogadores"] = Entidades::Entidade::getArrayJogadores();

		if (arquivo_fase.is_open()) {	// Verifica se o arquivo foi aberto
			/* Escreve tudo no arquivo (serializa), com uma indentação de 4 espaços pra tornar mais legível*/
			arquivo_fase << buffer_fase.dump(4);
			arquivo_fase.close();	// Fecha o arquivo e para a escrita

			std::cout << "Fase 1 salva em : " << "arquivo_fase.json" << std::endl;
		}
		else {
			std::cerr << "ERRO: Nao foi possivel abrir o arquivo da fase 2 para salvar." << std::endl;
		}
	}

	void FaseSegunda::salvarDataBuffer() {
		buffer_fase["fase"] = 2;
		if (pJog2) {
			buffer_fase["multiplayer"] = true;
		}
		else {
			buffer_fase["multiplayer"] = false;
		}
	}

	void FaseSegunda::carregar(const nlohmann::json& j) {
		try {
			lista_ents.remover(pJog1);
			if (pJog2) {
				lista_ents.remover(pJog2);
			}
			lista_ents.limpar();
			GC->limparListas();

			Fase::carregar(j, 2);

			carregarArmadilhas(j);
			carregarKitsunes(j);
		}
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: Alguma chave interna esta faltando." << e.what() << std::endl;
		}
	}
}
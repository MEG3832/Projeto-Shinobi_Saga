#include "FasePrimeira.h"
#include "Samurai_Inimigo.h"
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Redemoinho.h"

namespace Fases
{

	FasePrimeira::FasePrimeira():
		Fase(),
		maxSamurais(10),
		maxRedemoinhos(10)
	{
		criarCenario();

		sf::RectangleShape* pChao = pFundo->getChao();

		if (pChao) {
			GC->setChao(pChao);
			std::cout << "Chao configurado: " << pChao->getSize().x << "x" << pChao->getSize().y << std::endl;

			pJog->getCorpo()->setPosition(100.0f, ALTURA_TELA - pChao->getSize().y - pJog->getTam().y);
			pJog->getHitBox()->setPosition(pJog->getCorpo()->getPosition().x + (pJog->getCorpo()->getSize().x / 2 - pJog->getHitBox()->getSize().x / 2),
											pJog->getCorpo()->getPosition().y);
		}
		else
			std::cerr << "ERRO: pFundo nao retornou um chao!" << std::endl;

		criarInimigos();
		criarObstaculos();
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
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada3.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada4.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada5.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0f, "Imagens/JapanVillage/Camada6.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada7.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.5f, "Imagens/JapanVillage/Camada8.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize()), 0.0000005f, "Imagens/JapanVillage/Camada9.png");
		pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize().x, 80.0f));	// Chao
	}

	void FasePrimeira::criarInimigos()
	{
		criarTengus(); // está na classe base, já que a fase 2 também terá Tengus.
		criarSamurais();
	}

	void FasePrimeira::criarSamurais()
	{

		sf::RectangleShape* pChao = pFundo->getChao();
		float alturaChao = pChao ? pChao->getSize().y : 80.0f;

		const int min_samurais = 3;
		
		int qnt_inim = (rand() % (maxSamurais - min_samurais + 1)) + min_samurais; //gera valor entre minimo e maximo definido


		for (int i = 0; i < qnt_inim; i++)
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

				float posX = 300 + (i * 300.0f); // Espalha os inimigos
				float posY = pSam->getTam().y + 10.0f;
				if (pSam->getCorpo()) {
					pSam->getCorpo()->setPosition(posX, posY);
				}
				if (pSam->getHitBox()) {
					pSam->getHitBox()->setPosition(pSam->getCorpo()->getPosition().x + (pSam->getCorpo()->getSize().x / 2 - pSam->getHitBox()->getSize().x / 2),
												   pSam->getCorpo()->getPosition().y);
				}

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
		sf::RectangleShape* pChao = pFundo->getChao();
		float alturaChao = pChao ? pChao->getSize().y : 80.0f;

		const int min_red = 3;

		int qnt_red = (rand() % (maxRedemoinhos - min_red + 1)) + min_red; //gera valor entre minimo e maximo definido


		for (int i = 0; i < qnt_red; i++)
		{
			Entidades::Obstaculos::Redemoinho* pRed;
			pRed = new Entidades::Obstaculos::Redemoinho();

			if (pRed)
			{
				float posX = 200 + (i * 300.0f);
				float posY = ALTURA_TELA - alturaChao - pRed->getTam().y; 
				if (pRed->getCorpo()) {
					pRed->getCorpo()->setPosition(posX, posY);
				}
				if (pRed->getHitBox()) {
					pRed->getHitBox()->setPosition(pRed->getCorpo()->getPosition().x + (pRed->getCorpo()->getSize().x / 2 - pRed->getHitBox()->getSize().x / 2),
												   pRed->getCorpo()->getPosition().y);
				}

				GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(pRed));

				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(
											static_cast<Entidades::Obstaculos::Obstaculo*>(pRed));
				lista_ents.incluir(pEnt);
			}

			else
				std::cout << "Não foi possível alocar o redemoinho!" << std::endl;

		}
	}
}
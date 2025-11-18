#include "FaseSegunda.h"
#include "Kitsune.h"
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Inimigo.h"
#include "Armadilha_de_urso.h"
#include "Projetil.h"

namespace Fases
{

	FaseSegunda::FaseSegunda() :
		Fase(),
		maxKitsunes(8),
		maxArmadilhas(8)
	{
		altura_chao = 80.0;	// Medi olhando e testando

		fim_mapa = 10000;

		criarCenario();

		pJog->getCorpo()->setPosition(100.0f, ALTURA_TELA - altura_chao - pJog->getTam().y);
		pJog->getHitBox()->setPosition(pJog->getCorpo()->getPosition().x + (pJog->getCorpo()->getSize().x / 2 - pJog->getHitBox()->getSize().x / 2),
			pJog->getCorpo()->getPosition().y);

		criarObstaculos();
		criarInimigos();
	}

	FaseSegunda::~FaseSegunda()
	{

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

		int qnt_inim = (rand() % (maxKitsunes - min_kitsunes + 1)) + min_kitsunes; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Kitsune* pKits;
			pKits = new Entidades::Personagens::Kitsune(pJog);

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
		criarPlataformas(); //está lá na classe base

		criarArmadilhas();
	}

	void FaseSegunda::criarArmadilhas()
	{

		const int min_armad = 3;

		int qnt_armad = (rand() % (maxArmadilhas - min_armad + 1)) + min_armad; //gera valor entre minimo e maximo definido


		for (int i = 0; i < qnt_armad; i++)
		{
			Entidades::Obstaculos::Armadilha_de_urso* pArmad;
			pArmad = new Entidades::Obstaculos::Armadilha_de_urso();

			if (pArmad)
			{
				int correcao = 0;
				do {
					int posX = (2500 + i * 5000 + i * rand() % 800 + correcao) % fim_mapa;
					float posY = ALTURA_TELA - altura_chao - pArmad->getTam().y;
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
}
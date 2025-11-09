#include "FasePrimeira.h"
#include "Samurai_Inimigo.h"
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Inimigo.h"

namespace Fases
{

	FasePrimeira::FasePrimeira():
		Fase(),
		maxSamurais(10), //NOTA! tanto a quantidade de inimigos e obstáculos podem ser alterados...
		maxObstacFaceis(5), 
		maxObstacMedios(5)
	{
		criarCenario();

		sf::RectangleShape* pChao = pFundo->getChao();

		if (pChao) {

			pChao->setPosition(0.0f, ALTURA_TELA - pChao->getSize().y);
			GC->setChao(pChao);
			std::cout << "Chao configurado: " << pChao->getSize().x << "x" << pChao->getSize().y << std::endl;
		}
		else
			std::cerr << "ERRO: pFundo nao retornou um chao!" << std::endl;

		pJog->getCorpo()->setPosition(100.0f, ALTURA_TELA - pChao->getSize().y - pJog->getTam().y);
		pJog->getHitBox()->setPosition(pJog->getCorpo()->getPosition().x + (pJog->getCorpo()->getSize().x / 2 - pJog->getHitBox()->getSize().x / 2),
			pJog->getCorpo()->getPosition().y);

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
		pFundo->addCamada(sf::Vector2f(9000.0f, 80.0f), 0.0f, nullptr); //chao
		//pFundo->addCamada(sf::Vector2f(pGG->getWindow()->getSize().x, pGG->getWindow()->getSize().y - 80.0f));	// Chao
	}

	void FasePrimeira::criarInimigos()
	{
		criarTengus(); // está na classe base, já que a fase 2 também terá Tengus.
		criarSamurais();
		return;
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

				float posX = 100 + (i * 300.0f); // Espalha os inimigos
				float posY = ALTURA_TELA - alturaChao - pSam->getTam().y;
				pSam->getCorpo()->setPosition(posX, posY);

				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pSam);
				lista_ents.incluir(pEnt);
				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pSam));
			}

			else
				std::cout << "Não foi possível alocar o Samurai Inimigo!" << std::endl;

		}
	}

	void FasePrimeira::criarObstaculos()
	{
		//FAZER!!

		//criarPlataformas();
		//criarRedemoinhos();
		return;
	}
}
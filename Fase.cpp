#include "Fase.h"

namespace Fases
{
	Fase::Fase() :
		maxTengus(10),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		pJog(nullptr),
		pFundo(nullptr)
	{
		pJog = new Entidades::Personagens::Jogador(); //cria o jogador

		Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pJog); //coloca o jogador na lista de entidades
		lista_ents.incluir(pEnt);

		GC->setJogador(pJog); //por enquanto, só o jogador é setado no gerenc. de colisões

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
			lista_ents.aplicarGravidade();

			
			lista_ents.percorrer();

			
			GC->executar();

			
			if (pJog) {
				Ente::pGG->atualizaCamera(pJog->getPos());
			}

			
			if (pFundo)
				pFundo->executar();


			lista_ents.desenharEntidades();
	}

	void Fase::criarTengus()
	{
		sf::RectangleShape* pChao = pFundo->getChao();
		float alturaChao = pChao ? pChao->getSize().y : 80.0f;

		const int min_tengus = 3;

		int qnt_inim = (rand() % (maxTengus - min_tengus + 1)) + min_tengus; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(pJog); //temos que passar o endereço do jogador aqui...

			if (pTengu)
			{
				float posX = 600 + (i * 300.0f); // Espalha os inimigos
				float posY = ALTURA_TELA - alturaChao - pTengu->getTam().y;
				pTengu->getCorpo()->setPosition(posX, posY);

				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pTengu);
				lista_ents.incluir(pEnt);
				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pTengu));
			}

			else
				std::cout << "Não foi possível alocar o Tengu!" << std::endl;

		}

	}

	void Fase::criarPlataformas()
	{
		/*
		sf::RectangleShape* pChao = pFundo->getChao();
		float alturaChao = pChao ? pChao->getSize().y : 80.0f;

		const int min_plataf = 3;

		int qnt_inim = (rand() % (maxPlataf - min_plataf + 1)) + min_plataf; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(pJog); //temos que passar o endereço do jogador aqui...

			if (pTengu)
			{
				float posX = 400 + (i * 300.0f); // Espalha os inimigos
				float posY = ALTURA_TELA - alturaChao - pTengu->getTam().y;
				pTengu->getCorpo()->setPosition(posX, posY);

				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pTengu);
				lista_ents.incluir(pEnt);
				GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pTengu));
			}

			else
				std::cout << "Não foi possível alocar o Tengu!" << std::endl;

		}
		*/
		return;
	}


}

//int Fases::Fase::maxTengus = 10;
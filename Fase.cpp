#include "Fase.h"

namespace Fases
{
	Fase::Fase() :
		maxTengus(5),
		maxPlataf(8),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		pJog(nullptr),
		pFundo(nullptr),
		fim_mapa(0)
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
			GC->executar();

			lista_ents.percorrer();

			lista_ents.aplicarGravidade();

			if (pJog) {
				Ente::pGG->atualizaCamera(pJog->getPos());
			}
			
			if (pFundo)
				pFundo->executar();

			lista_ents.desenharEntidades();

			//teste
			if (pJog->getCorpo()->getPosition().x >= fim_mapa) {
				std::cout << "fim!!" << std::endl;
			}
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
				int correcao = 0;

				do {
					int posX = (1000 + i * 4000 + i * rand() % 1000 + correcao) % fim_mapa;
					int posY = pGG->getWindow()->getSize().y - alturaChao - pTengu->getCorpo()->getSize().y;

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
		
		sf::RectangleShape* pChao = pFundo->getChao();
		float alturaChao = pChao ? pChao->getSize().y : 80.0f;

		const int min_plataf = 3;

		int qnt_plataf = (rand() % (maxPlataf - min_plataf + 1)) + min_plataf; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_plataf; i++)
		{
			Entidades::Obstaculos::Plataforma* pPlataf;
			pPlataf = new Entidades::Obstaculos::Plataforma();

			if (pPlataf)
			{ 
				int correcao = 0;

				do {
					int posX = (300 + i * 4500 + i * rand() % 1500 + correcao) % fim_mapa;
					int posY = ALTURA_TELA - alturaChao - pPlataf->getTam().y -
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


}

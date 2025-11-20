#include "Fase.h"

namespace Fases
{
	Fase::Fase(Entidades::Personagens::Jogador* pJog1) :
		pJog1(pJog1),
		pJog2(nullptr),
		maxTengus(5),
		maxPlataf(8),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		//pJog(nullptr),
		pFundo(nullptr),
		fim_mapa(0),
		altura_chao(0.0)
	{
		Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pJog1); //coloca o jogador na lista de entidades
		lista_ents.incluir(pEnt);

		GC->setJogador1(pJog1);
		GC->setJogador2(nullptr);

		pFundo = new Parallax::Fundo(); //cria o fundo

	}

	Fase::Fase(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2) :
		pJog1(pJog1),
		pJog2(pJog2),
		maxTengus(5),
		maxPlataf(8),
		lista_ents(),
		GC(GC->getGerenciadorColisoes()),
		//pJog(nullptr),
		pFundo(nullptr),
		fim_mapa(0),
		altura_chao(0.0)
	{
		Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pJog1); //coloca o jogador na lista de entidades
		Entidades::Entidade* pEnt2 = static_cast<Entidades::Entidade*>(pJog2); //coloca o jogador na lista de entidades
		lista_ents.incluir(pEnt);
		lista_ents.incluir(pEnt2);

		GC->setJogador1(pJog1);
		GC->setJogador2(pJog2);

		pFundo = new Parallax::Fundo(); //cria o fundo

	}

	Fase::~Fase()
	{
		//retiramos os jogadores da lista para que eles não sejam destruídos quando a fase acabar...
		if (pJog1) {
			lista_ents.remover(static_cast<Entidades::Entidade*>(pJog1));
		}
		if (pJog2) {
			lista_ents.remover(static_cast<Entidades::Entidade*>(pJog2));
		}

		lista_ents.limpar();

		if (pFundo) {
			delete pFundo;
			pFundo = nullptr;
		}

		// não deletamos o GC aqui, pois ele é Singleton usado pelo Jogo inteiro.
		//A lista de entidades já é limpada ao ser destruída (lista_ents é da classe Lista_Entidades, q possui uma Lista parametrizada com Entidades)
	}

	void Fase::executar()
	{
			GC->executar();

			lista_ents.percorrer();

			lista_ents.aplicarGravidade();

			//a câmera centraliza no jogador 1...
			if (pJog1) {
				Ente::pGG->atualizaCamera(pJog1->getPos());
			}
			
			if (pFundo)
				pFundo->executar();

			lista_ents.desenharEntidades();

			//basta o primeiro jogador chegar no final...
			if (pJog1->getCorpo()->getPosition().x >= fim_mapa) {
				std::cout << "fim!!" << std::endl;
			}
	}

	void Fase::criarTengus()
	{

		const int min_tengus = 3;

		int qnt_inim = (rand() % (maxTengus - min_tengus + 1)) + min_tengus; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(pJog1,pJog2); //temos que passar o endereço do jogador aqui...

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

	/*Entidades::Personagens::Jogador* Fase::getJogador() {
		return pJog;
	}*/


}

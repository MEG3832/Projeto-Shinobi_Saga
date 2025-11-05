#include "FasePrimeira.h"
#include "Fase.h"
#include "Samurai_Inimigo.h"
#include "Entidade.h"
#include "ListaEntidades.h"

namespace Fases
{

	FasePrimeira::FasePrimeira():
		Fase(),
		maxSamurais(10), //NOTA! tanto a quantidade de inimigos e obstáculos podem ser alterados...
		maxTengus(10),
		maxObstacFaceis(5), 
		maxObstacMedios(5)
	{
		criarInimigos();
		criarObstaculos();
		executar();
	}

	FasePrimeira::~FasePrimeira()
	{

	}

	void FasePrimeira::criarInimigos()
	{
		criarTengus(); // está na classe base, já que a fase 2 também terá Tengus.
		criarSamurais();
	}

	void criarSamurais()
	{
		const int min_samurais = 3;
		
		int qnt_inim = (rand() % (maxSamurais - min_samurais + 1)) + min_samurais; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Samurai_Inimigo* pSam;
			pSam = new Samurai_Inimigo();

			if (pSam)
			{
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pSam);
				lista_ents.incluir(pEnt);
				GC.incluirInimigo(pSam);
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
	}
}
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
		//criarInimigos(); ->não precisa disso né? já que chamamosa construtora de Fase explicitamente...
		//criarObstaculos(); ->nem disso?
		executar();
	}

	FasePrimeira::~FasePrimeira()
	{

	}

	void FasePrimeira::criarInimigos()
	{
		//criarTengus(); // está na classe base, já que a fase 2 também terá Tengus.
		//criarSamurais();
		return;
	}

	/*void FasePrimeira::criarSamurais()
	{

		//POSSO SORTEAR DE UM NUMERO ENTRE 1, 2 OU 3 para definir o tamanho.

		const int min_samurais = 3;
		
		int qnt_inim = (rand() % (maxSamurais - min_samurais + 1)) + min_samurais; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Samurai_Inimigo* pSam;
			pSam = new Entidades::Personagens::Samurai_Inimigo(); //?

			if (pSam)
			{
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pSam);
				lista_ents.incluir(pEnt);
				GC.incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pSam));
			}

			else
				std::cout << "Não foi possível alocar o Samurai Inimigo!" << std::endl;

		}
	}*/

	void FasePrimeira::criarObstaculos()
	{
		//FAZER!!

		//criarPlataformas();
		//criarRedemoinhos();
		return;
	}
}
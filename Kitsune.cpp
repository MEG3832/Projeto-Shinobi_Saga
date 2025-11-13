#include "Kitsune.h"

namespace Entidades
{
	namespace Personagens
	{
		Kitsune::Kitsune(Jogador* pJ) :
			Inimigo(pJ),
			pProj(nullptr)
		{
			raio_ativacao = 50.0f;
			tempo_cooldown = 5.0f;
		}

		Kitsune::~Kitsune()
		{
			pProj = nullptr;
		}

		void Kitsune::mover()
		{
			Inimigo::perambular(); //posso fazer isso, né?
		}

		void Kitsune::criaProjetil()
		{
			Projetil* pProj = new Entidades::Projetil();



		}

	}
}
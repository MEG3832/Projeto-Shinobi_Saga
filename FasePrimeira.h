#pragma once
#include "Fase.h"

namespace Fases {

	class Fase;

	class FasePrimeira : public Fase
	{
	private:

		const int maxSamurais;
		const int maxRedemoinhos;

	public:

		FasePrimeira();
		~FasePrimeira();

		//reimplementação dos métodos virtuais puros:
		void criarCenario();
		void criarInimigos();
		void criarObstaculos();

		// ---- //

		void criarSamurais(); //inimigo exclusivo da fase 1!
		void criarRedemoinhos(); //obstáculo exclusivo da fase 1!

	};

}


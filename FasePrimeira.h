#pragma once
#include "Fase.h"

namespace Fases {

	class Fase;

	class FasePrimeira : public Fase
	{
	private:

		const int maxSamurais;
		//const int maxTengus; ->já temos na classe base!
		const int maxObstacFaceis; //mudar nome dps para o específico
		const int maxObstacMedios;

	public:

		FasePrimeira();
		~FasePrimeira();

		//reimplementação dos métodos virtuais puros:
		void criarCenario();
		void criarInimigos();
		void criarObstaculos();

		// ---- //

		void criarSamurais(); //inimigo exclusivo da fase 1!

	};

}


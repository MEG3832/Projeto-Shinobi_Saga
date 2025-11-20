#pragma once
#include "Fase.h"
#include "Kitsune.h"

namespace Fases {

	class Fase;

	class FaseSegunda : public Fase
	{
	private:

		const int maxKitsunes;
		const int maxArmadilhas;

	public:

		FaseSegunda();
		~FaseSegunda();

		// Reimplementacoes
		void criarCenario();
		void criarInimigos();
		void criarObstaculos();
		void salvar();
		void salvarDataBuffer();
		void carregar(const nlohmann::json& j);

		void criarProjetil(Entidades::Personagens::Kitsune* pKits);
		void criarKitsunes(); //inimigo exclusivo da fase 2!
		void criarArmadilhas(); //obstáculo exclusivo da fase 2!
		Entidades::Projetil* carregarProjetil(const nlohmann::json& j, Entidades::Personagens::Kitsune* pKits, int i);
		void carregarKitsunes(const nlohmann::json& j); 
		void carregarArmadilhas(const nlohmann::json& j); 

	};

}

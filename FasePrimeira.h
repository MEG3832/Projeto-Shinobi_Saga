#pragma once
#include "Fase.h"

namespace Fases {

	class Fase;

	class FasePrimeira : public Fase
	{
	private:

		const int maxSamurais;
		const int maxRedemoinhos;
		int qnt_samurais;
		int qnt_redemoinhos;

	public:

		FasePrimeira();
		~FasePrimeira();

		// Reimplementacoes
		void criarCenario();
		void criarInimigos();
		void criarObstaculos();

		void criarSamurais(); //inimigo exclusivo da fase 1!
		void criarRedemoinhos(); //obstáculo exclusivo da fase 1!

		void carregarSamurais();
		void carregarRedemoinhos(const nlohmann::json& j);

		void salvar();
		void salvarDataBuffer();
		void carregar(const nlohmann::json& j);
	};

}


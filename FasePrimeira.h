#pragma once
#include "Fase.h"
#include "Jogador.h"

namespace Fases {

	class Fase;

	class FasePrimeira : public Fase
	{
	private:

		const int maxSamurais;
		const int maxRedemoinhos;

	public:

		FasePrimeira(Entidades::Personagens::Jogador* pJog1);
		FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2);
		~FasePrimeira();

		// Reimplementacoes
		void criarCenario();
		void criarInimigos();
		void criarObstaculos();

		void criarSamurais(); //inimigo exclusivo da fase 1!
		void criarRedemoinhos(); //obstáculo exclusivo da fase 1!

		void carregarSamurais(const nlohmann::json& j);
		void carregarRedemoinhos(const nlohmann::json& j);

		void salvar();
		void salvarDataBuffer();
		void carregar(const nlohmann::json& j);
	};

}


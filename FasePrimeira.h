/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

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

		void criarCenario();
		void criarInimigos();
		void criarObstaculos();
		void carregarSamurais(const nlohmann::json& j);
		void carregarRedemoinhos(const nlohmann::json& j);
		void salvarDataBuffer();

	protected:
		void criarSamurais(); //inimigo exclusivo da fase 1!
		void criarRedemoinhos(); //obstáculo exclusivo da fase 1!


	public:

		FasePrimeira(Entidades::Personagens::Jogador* pJog1 = nullptr);
		FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2);
		~FasePrimeira();

		void salvar();
		void carregar(const nlohmann::json& j);
	};

}


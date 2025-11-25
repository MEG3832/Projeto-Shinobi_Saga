/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

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

		void criarCenario();
		void criarInimigos();
		void criarObstaculos();
		void carregarKitsunes(const nlohmann::json& j);
		void carregarArmadilhas(const nlohmann::json& j);
		Entidades::Projetil* carregarProjetil(const nlohmann::json& j, Entidades::Personagens::Kitsune* pKits, const int i);
		void salvarDataBuffer();


	protected:
		void criarProjetil(Entidades::Personagens::Kitsune* pKits);
		void criarKitsunes(); //inimigo exclusivo da fase 2!
		void criarArmadilhas(); //obstáculo exclusivo da fase 2!


	public:

		FaseSegunda(Entidades::Personagens::Jogador* pJog1 = nullptr);
		FaseSegunda(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2);
		~FaseSegunda();

		// Reimplementacoes
		void salvar();
		void carregar(const nlohmann::json& j);
	};

}

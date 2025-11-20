#pragma once
#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		class Armadilha_de_urso :  public Obstaculo
		{
		private:
			float lado;
			short int danosidade;
			float cooldown_atordoamento;
			sf::Clock timer;
			
			// Variaveis
			float dt;	// Nao testei essa mudanca do dt

		public:
			Armadilha_de_urso();
			~Armadilha_de_urso();
			
			void inicializaAnimacoes();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);

			// Reimplementacoes
			void executar();
			void obstaculizar(Personagens::Jogador* pJ);
			void salvar();
			void atualizaAnimacao();
		};

	}

}
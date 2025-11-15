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
			float dt;

			// Variaveis
			sf::Clock timer;

		public:
			Armadilha_de_urso();
			~Armadilha_de_urso();
			
			void inicializaAnimacoes();
			void salvarDataBuffer();

			// Reimplementacoes
			void executar();
			void obstaculizar(Personagens::Jogador* pJ);
			void salvar();
			void atualizaAnimacao();
		};

	}

}
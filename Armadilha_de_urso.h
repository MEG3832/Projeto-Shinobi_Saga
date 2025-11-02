#pragma once
#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		class Armadilha_de_urso :  public Obstaculo
		{
		private:
			int altura;
			int comprimento;
			short int danosidade;
			float cooldown;
			sf::Clock timer;
			float dt;

		public:
			Armadilha_de_urso();
			~Armadilha_de_urso();
			void executar();
			void obstaculizar(Personagens::Jogador* pJ);
			void salvar();
			void inicializaAnimacoes();
			void atualizaAnimacao();
			void salvarDataBuffer();
		};

	}

}
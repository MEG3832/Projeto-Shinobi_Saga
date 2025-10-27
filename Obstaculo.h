#pragma once
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
			protected:
				bool danoso;

			public:
				Obstaculo();
				~Obstaculo();
				void salvarDataBuffer();
				virtual void executar();
				virtual void salvar();
				virtual void obstaculizar(Personagens::Jogador* pJ);
				virtual void inicializaAnimacoes();
		};

	}

}
#pragma once
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
			protected:

				// Variaveis
				bool danoso;

			public:
				Obstaculo();
				~Obstaculo();

				void salvarDataBuffer(nlohmann::json& buffer);
				virtual void carregar(const nlohmann::json& j);
				virtual void sofrerContraForca();

				// Abstratas
				virtual void executar() = 0;
				virtual void salvar() = 0;
				virtual void obstaculizar(Personagens::Jogador* pJ) = 0;
		};

	}

}
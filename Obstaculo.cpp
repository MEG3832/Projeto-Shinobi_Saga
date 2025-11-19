#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		Obstaculo::Obstaculo() :
			Entidade(),
			danoso(false)
		{}

		Obstaculo::~Obstaculo() 
		{}

		void Obstaculo::salvarDataBuffer(nlohmann::json& buffer) {

			Entidade::salvarDataBuffer(buffer);

			buffer["danoso"] = false;
		}

		void Obstaculo::sofrerContraForca() {
			float aceleracao = -GRAVIDADE;
			veloc.y += aceleracao;
		}

	}

}
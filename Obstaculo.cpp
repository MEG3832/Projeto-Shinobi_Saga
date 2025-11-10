#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		Obstaculo::Obstaculo() :
			Entidade(),
			danoso(false)
		{}

		Obstaculo::~Obstaculo() 
		{}

		void Obstaculo::salvarDataBuffer() {
			return;
		}

		void Obstaculo::sofrerContraForca() {
			float aceleracao = -GRAVIDADE;
			veloc.y += aceleracao;
		}

	}

}
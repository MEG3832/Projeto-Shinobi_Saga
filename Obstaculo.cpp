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

		void Obstaculo::desenhar() {	// Por ser virtual (o que eu não sei se pode), por enquanto não faz nada
			pGG->desenharEnte(static_cast<Ente*>(
							  static_cast<Entidade*>(this)));
		}

	}

}
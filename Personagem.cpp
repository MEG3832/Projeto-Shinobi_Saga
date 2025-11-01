#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(5000),
			id(-1),
			dano(-1)
		{}

		Personagem::~Personagem()
		{
			num_vidas = -1;
			delete animador;
			animador = nullptr;
		}

		void Personagem::diminuiVida(float dano) {
			if (num_vidas > 0) {
				num_vidas--;
			}
			std::cout << num_vidas << std::endl;
		}

		//int Personagem::getNumVidas()
		//{

		//}

		//void Personagem::getDano()
		//{
			
		//}

	}

}
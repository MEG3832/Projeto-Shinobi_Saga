#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(3),
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
			if (num_vidas - dano < 0) {
				num_vidas -= (dano - num_vidas);
			}
			else if (num_vidas > 0) {
				num_vidas -= dano;
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
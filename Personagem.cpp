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

		void Personagem::diminuiVida(int dano) {
			if (num_vidas - dano <= 0) {
				num_vidas = 0;
			}
			else {
				num_vidas -= dano;
			}
			std::cout << num_vidas << std::endl;
		}

		int Personagem::getVida()
		{
			return num_vidas;
		}

		int Personagem::getDano()
		{
			return dano;
		}

	}

}
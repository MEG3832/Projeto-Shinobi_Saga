#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(0),
			dano(-1),
			paraEsq(false),
			dt(0),
			timer()
		{}

		Personagem::~Personagem()
		{
			num_vidas = -1;
			delete animador;
			animador = nullptr;
		}

		void Personagem::diminuiVida(float dano) {
			if (num_vidas - dano < 0) {
				num_vidas -= num_vidas;
			}
			else if (num_vidas > 0) {
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

		void Personagem::setNoChao() {
			veloc.y = 0.0f;
		}

	}

}
#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(3),
			id(1),
			dano(-1),
			morrendo(false),
			paraEsq(false),
			ferido(false),
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
				num_vidas -= (dano - num_vidas);
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

		bool Personagem::getFerido() {	// Usado no Gerenciador de Eventos
			return ferido;
		}

		//void Personagem::getDano()
		//{
			
		//}
		int Personagem::getDano()
		{
			return dano;
		}

	}

}
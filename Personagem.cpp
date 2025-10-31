#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(0),
			id(-1),
			dano(-1)
		{}

		Personagem::~Personagem()
		{
			num_vidas = -1;
			delete animador;
			animador = nullptr;
		}

		//int Personagem::getNumVidas()
		//{

		//}

		//float Personagem::getDano()
		//{

		//}

	}

}
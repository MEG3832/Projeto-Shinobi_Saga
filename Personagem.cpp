#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(0)
		{
		}

		Personagem::~Personagem()
		{
			num_vidas = -1;
		}

	}

}
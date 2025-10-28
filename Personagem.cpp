#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(0),
			id(-1),
			animador(nullptr),
			dano(-1)
		{}

		Personagem::~Personagem()
		{
			num_vidas = -1;
			delete animador;
			animador = nullptr;
		}

		void Personagem::setAnimador(sf::RectangleShape* body) {
			animador = new Animadores::Animacao(body);
		}


		//int Personagem::getNumVidas()
		//{

		//}

		//float Personagem::getDano()
		//{

		//}

	}

}
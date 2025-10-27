#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(0)
		{
			animador = new Animadores::Animacao(corpo); //mudar para corpo!!
		}

		Personagem::~Personagem()
		{
			num_vidas = -1;
			delete animador;
			animador = nullptr;
		}

		/*void Personagem::executar()
		{
		}*/

		/*void Personagem::salvar()
		{
		}*/

		void Personagem::mover()
		{
		}

		//int Personagem::getNumVidas()
		//{

		//}
		//float Personagem::getDano()
		//{

		//}

		void Personagem::inicializaAtributos()
		{

		}

	}

}
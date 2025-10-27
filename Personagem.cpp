#include "Personagem.h"

<<<<<<< HEAD
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
=======
Personagem::Personagem():
	Entidade(),
	id(-1),
	dano(0.0),
	num_vidas(0)
{
	animador = new Animadores::Animacao(pFig);

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
>>>>>>> animation

#include "Personagem.h"

Personagem::Personagem():
	Entidade(),
	id(-1)
{
	animador = new Animacao(&body);

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

int Personagem::getNumVidas()
{

}
float Personagem::getDano()
{

}

void Personagem::inicializaAtributos()
{

}

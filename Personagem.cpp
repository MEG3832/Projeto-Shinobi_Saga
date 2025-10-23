#include "Personagem.h"

Personagem::Personagem() :
	Entidade(),
	num_vidas(0)
{
}

Personagem::~Personagem()
{
	num_vidas = -1;
}
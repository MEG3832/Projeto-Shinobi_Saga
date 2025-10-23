#include "Personagem.h"

Personagem::Personagem():
	Entidade(), //recebe medidas do rectangle shape
	num_vidas(0)
{
	animador = new Animacao(&body);

}

Personagem::~Personagem()
{
	num_vidas = -1;
	delete animador;
	animador = nullptr;
}

void Personagem::executar()
{
}

void Personagem::salvar()
{
}

void Personagem::mover()
{
}
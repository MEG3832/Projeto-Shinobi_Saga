#pragma once

#include "Personagem.h"
#include "Header.h"

class Jogador:public Personagem
{
protected:

	int pontos;
	int id; // 1 ou 2 (?)
	//...

public:

	Jogador(int ident); //com parâmetro
	Jogador(); // sem parâmetro
	~Jogador();
	//void colidir(Inimigo* pIn);
	void executar();
	void salvar();
	void mover();
	//...
};


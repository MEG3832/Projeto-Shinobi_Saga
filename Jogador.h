#pragma once

#include "Personagem.h"
#include "Header.h"

class Jogador:public Personagem
{
protected:

	int pontos;

	//!!!!!!!!talvez rastrear esse tipo de coisa apenas para o jogador...
	bool paraEsq;
	bool subindo;
	bool caindo;
		
	//...

public:

	Jogador(); //com parâmetro
	~Jogador();
	//void colidir(Inimigo* pIn);
	//void executar();
	//void salvar();
	void mover();
	void inicializaAtributos();
	void inicializaAnimacoes();
	void atualizaAnimacao();
	float getDano();
	//...
};


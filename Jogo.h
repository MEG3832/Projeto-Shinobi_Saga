#pragma once

#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
#include "Fase.h"
#include "FasePrimeira.h"
#include "Ente.h"
#include "Menu.h"


class Jogo {
private:
	Menu menu;
	Gerenciadores::Gerenciador_Grafico* pGG;
	Gerenciadores::Gerenciador_de_Eventos* pGE;
	Fases::FasePrimeira* pFase1; //o jogador é criado na fase!
	int fase;

public:
	Jogo();
	~Jogo();
	void criarFase();
	void executar();
	void setFase(int num);
};

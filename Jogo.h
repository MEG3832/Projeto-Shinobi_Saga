#pragma once

#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
#include "Fase.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"
#include "Ente.h"
#include "Menu.h"
#include "Jogador.h"


class Jogo {
	private:

		enum Estado {
			MENU_PRINCIPAL,
			MENU_PAUSA,
			FASE1,
			FASE2
		};

		Menu menu;
		Gerenciadores::Gerenciador_Grafico* pGG;
		Gerenciadores::Gerenciador_de_Eventos* pGE;
		Fases::FasePrimeira* pFase1; 
		Fases::FaseSegunda* pFase2;
		Entidades::Personagens::Jogador* pJog1;
		Entidades::Personagens::Jogador* pJog2;

		// Variaveis
		Estado estado_atual;
	

	public:
		Jogo();
		~Jogo();
		void executar();
		void setFase(int num);
};

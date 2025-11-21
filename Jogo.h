#pragma once

#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
#include "Fase.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"
#include "Ente.h"
#include "Menu_Principal.h"
#include "Menu_Pause.h"


class Jogo {
	private:

		enum Estado {
			MENU_PRINCIPAL,
			MENU_PAUSE,
			MENU_COLOCACAO,
			FASE1,
			FASE2
		};

		Menu_Principal menu_principal;
		Menu_Pause menu_pause;
		Gerenciadores::Gerenciador_Grafico* pGG;
		Gerenciadores::Gerenciador_de_Eventos* pGE;
		Fases::FasePrimeira* pFase1; 
		Fases::FaseSegunda* pFase2; 
		Entidades::Personagens::Jogador* pJog1;
		Entidades::Personagens::Jogador* pJog2;


		// Variaveis
		Estado estado_atual;
		Estado estado_anterior;
	

	public:
		Jogo();
		~Jogo();
		void executar();
		void setEstado(int num);
		void voltarEstado();
		void setFase(Fases::FasePrimeira* pF1, Fases::FaseSegunda* pF2);
};

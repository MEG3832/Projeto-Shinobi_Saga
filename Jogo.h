#pragma once

#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
#include "Fase.h"
#include "FasePrimeira.h"
#include "Ente.h"
#include "Menu.h"
#include "Menu_Fase.h"


class Jogo {
	private:

		enum Estado {
			MENU_PRINCIPAL,
			MENU_PAUSA,
			MENU_FASE,
			FASE1,
			FASE2
		};

		Menu menu;
		Menu_Fase menu_fase;
		Gerenciadores::Gerenciador_Grafico* pGG;
		Gerenciadores::Gerenciador_de_Eventos* pGE;
		Fases::FasePrimeira* pFase1; //o jogador é criado na fase!

		// Variaveis
		Estado estado_atual;
		Estado estado_anterior;
	

	public:
		Jogo();
		~Jogo();
		void criarFase();
		void executar();
		void setFase(int num);
		void setEstadoMenuFases();
		void voltarEstado();
};

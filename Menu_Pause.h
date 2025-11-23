#pragma once
#include "Menu.h"
#include "Fase.h"

class Menu_Pause : public Menu
{
	private:
		Fases::Fase* pFase;	// Essa eh a fase que será salva


	public:	
		Menu_Pause();
		~Menu_Pause();
		void executar();
		void inicializaTexto();
		void desenharTexto();
		void setFase(Fases::Fase* pF);
};


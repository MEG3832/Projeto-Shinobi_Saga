#pragma once
#include "Menu.h"
#include "Fase.h"

class Menu_Pause : public Menu
{
	private:
		Fases::Fase* pFase;	// Essa eh a fase que será salva

		void inicializaTexto();
		void desenharTexto();

	public:	
		Menu_Pause();
		~Menu_Pause();
		void executar();
		void setFase(Fases::Fase* pF);
};


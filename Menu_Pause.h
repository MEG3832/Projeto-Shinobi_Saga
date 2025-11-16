#pragma once
#include "Menu.h"

class Menu_Pause : public Menu
{
	public:	// fica muito feio fazer com tao poucos atributos?
		Menu_Pause();
		~Menu_Pause();
		void executar();
		void inicializaFundo();	// Pensei em fazer um rand com os fundos de ambas as telas de fundo das fases
		void inicializaTexto();
};


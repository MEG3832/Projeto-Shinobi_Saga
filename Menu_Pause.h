#pragma once
#include "Menu.h"

class Menu_Pause : public Menu
{
	public:	// fica muito feio fazer com tao poucos atributos?
		Menu_Pause();
		~Menu_Pause();
		void executar();
		void inicializaTexto();
};


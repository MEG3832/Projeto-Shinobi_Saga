#pragma once
#include "Menu.h"

class Menu_Fase : public Menu
{
	public:	// fica muito feio fazer com tao poucos atributos?
		Menu_Fase();
		~Menu_Fase();
		void executar();
		void inicializaTexto();
};


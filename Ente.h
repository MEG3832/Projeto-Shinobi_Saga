#pragma once
#include "Gerenciador_Grafico.h"
class Ente
{
	protected:
		sf::CircleShape* pFig;

		static Gerenciador_Grafico* pGG;

	public:
		Ente();
		virtual ~Ente();
		void desenhar();

		static void setGG(Gerenciador_Grafico* pG);
};


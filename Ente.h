#pragma once
#include "Gerenciador_Grafico.h"
class Ente
{
	protected:
		sf::CircleShape* pFig;
		static Gerenciadores::Gerenciador_Grafico* pGG;

	public:
		Ente();
		virtual ~Ente();
		virtual void desenhar();	// Não sei se podia fazer isso, mas deixei desenhar() como virtual para o Fundo

		static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
};


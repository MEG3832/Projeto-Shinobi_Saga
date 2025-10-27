#pragma once
#include "Gerenciador_Grafico.h"
class Ente
{
	protected:
<<<<<<< HEAD
		static Gerenciadores::Gerenciador_Grafico* pGG;
		sf::RectangleShape* corpo;
=======
		sf::RectangleShape* pFig;
		static Gerenciador_Grafico* pGG;
>>>>>>> animation

	public:
		Ente();
		virtual ~Ente();
		virtual void desenhar();	// Não sei se podia fazer isso, mas deixei desenhar() como virtual para o Fundo
		virtual void executar() = 0;
		sf::Vector2f getTam();

		static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
};


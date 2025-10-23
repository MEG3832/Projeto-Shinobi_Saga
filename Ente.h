#pragma once
#include "Gerenciador_Grafico.h"
class Ente
{
	protected:
		static Gerenciadores::Gerenciador_Grafico* pGG;
		sf::RectangleShape* corpo;

	public:
		Ente();
		virtual ~Ente();
		virtual void desenhar();	// Não sei se podia fazer isso, mas deixei desenhar() como virtual para o Fundo
		virtual void executar() = 0;

		static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
};


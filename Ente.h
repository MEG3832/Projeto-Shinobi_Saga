#pragma once
#include "Gerenciador_Grafico.h"
class Ente
{
	protected:
		int id;
		static Gerenciadores::Gerenciador_Grafico* pGG;
		sf::RectangleShape* corpo;

	public:
		Ente();
		virtual ~Ente();
		void desenhar();	// Não sei se podia fazer isso, mas deixei desenhar() como virtual para o Fundo
		virtual void executar() = 0;
		sf::Vector2f getTam();
		sf::RectangleShape* getCorpo();

		static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
};


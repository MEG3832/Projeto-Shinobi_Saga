#pragma once
#include "Gerenciador_Grafico.h"
class Ente
{
	protected:
		static Gerenciadores::Gerenciador_Grafico* pGG;
		sf::RectangleShape* corpo;
		sf::RectangleShape* hitBox;

	public:
		Ente();
		virtual ~Ente();

		void desenhar();
		sf::Vector2f getTam();	// Nao usei, posso tirar? corpo->getSize() eh equivalente
		sf::RectangleShape* getCorpo();
		sf::RectangleShape* getHitBox();

		// Reimplementacoes
		virtual void executar() = 0;

		// Estaticas
		static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
};


/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

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
		sf::RectangleShape* getCorpo();
		sf::RectangleShape* getHitBox();

		// Reimplementacoes
		virtual void executar() = 0;

		// Estaticas
		static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
};


#pragma once
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Tengu.h"

namespace Fases {

	class Fase
	{
	protected:

		static const int maxTengus;
		sf::RectangleShape chao;

		Listas::ListaEntidades lista_ents;
		Gerenciadores::Gerenciador_Colisoes GC;


	public:

		Fase(); //->cria os inimigos, obstáculos dinamicamente e põe da lista de entidades...
		~Fase();

		virtual void executar(); // ->percorre a lista de entidades...

	protected:

		virtual void criarInimigos() = 0 ;
		virtual void criarObstaculos() = 0;

		void criarCenario();
		void criarTengus(); //inimigos em comum nas duas fases.
		//void criarSamurais();
		//void criarKitsunes();
		


	};

}




#pragma once
#include "Gerenciador_Grafico.h"
#include "Jogador.h"

namespace Gerenciadores {

	class Gerenciador_de_Eventos
	{
		private:
			Gerenciador_Grafico* pGrafico;
			Entidades::Personagens::Jogador* pJogador;

			static Gerenciador_de_Eventos* pEventos;
			Gerenciador_de_Eventos();

		public:
			~Gerenciador_de_Eventos();
			static Gerenciador_de_Eventos* getGerenciadorEventos();
			void setJogador(Entidades::Personagens::Jogador* pJogador);
			void verificaTeclaPressionada();
			void executar();
	};

}
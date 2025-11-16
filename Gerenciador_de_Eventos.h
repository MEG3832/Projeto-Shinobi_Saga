#pragma once
#include "Gerenciador_Grafico.h"
#include "Jogador.h"

class Jogo;
class Menu;

namespace Gerenciadores {

	class Gerenciador_de_Eventos
	{
		private:
			Gerenciador_Grafico* pGrafico;
			Entidades::Personagens::Jogador* pJogador;
			Jogo* pJogo;

			static Gerenciador_de_Eventos* pEventos;
			Gerenciador_de_Eventos();

		public:
			~Gerenciador_de_Eventos();
			static Gerenciador_de_Eventos* getGerenciadorEventos();
			void setJogador(Entidades::Personagens::Jogador* pJogador);
			void verificaTeclaPressionada();
			void executar();
			void executarMenu(Menu* pMenu);
			void verificaTeclaPressionadaMenu(Menu* pMenu, sf::Keyboard::Key tecla);
			void setJogo(Jogo* pJ);
	};

}
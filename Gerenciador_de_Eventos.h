#pragma once
#include "Gerenciador_Grafico.h"
#include "Jogador.h"

class Jogo;
class Menu;
class Menu_Salvamento_Ranking;

namespace Gerenciadores {

	class Gerenciador_de_Eventos
	{
		private:
			Gerenciador_Grafico* pGrafico;
			Entidades::Personagens::Jogador* pJogador1;
			Entidades::Personagens::Jogador* pJogador2;
			Entidades::Personagens::Jogador* pJogador;
			Jogo* pJogo;

			static Gerenciador_de_Eventos* pEventos;
			Gerenciador_de_Eventos();

		public:
			~Gerenciador_de_Eventos();
			static Gerenciador_de_Eventos* getGerenciadorEventos();
			void setJogador1(Entidades::Personagens::Jogador* pJogador);
			void setJogador2(Entidades::Personagens::Jogador* pJogador);
			void verificaTeclaPressionada();
			void executar();
			void executarMenu(Menu* pMenu);
			void executarMenuSave(Menu_Salvamento_Ranking* pMenu);
			void verificaTeclaPressionadaMenu(Menu* pMenu, sf::Keyboard::Key tecla);
			void verificaTeclaPressionadaMenuSave(Menu_Salvamento_Ranking* pMenu, sf::Keyboard::Key tecla);
			void setJogo(Jogo* pJ);
	};

}
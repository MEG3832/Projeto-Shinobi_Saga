#pragma once
#include "Menu.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"

class Menu_Principal : public Menu
{
	private:

		enum Estado {
			PRINCIPAL,
			SELECAO_FASE,
			SELECAO_MULTIPLAYER
		};

		std::vector<sf::Text> texto_principal;
		std::vector<sf::Text> texto_selecaoFase;
		std::vector<sf::Text> texto_selecaoMultiplayer;
		sf::Text titulo;
		Estado estado_atual;

		void inicializaTexto();
		void inicializaTexto_SelecaoFase();
		void inicializaTexto_SelecaoMultiplayer();
		void inicializaTexto_Principal();
		void desenharTexto();
		void copiarVetores(std::vector<sf::Text> origem, std::vector<sf::Text>* destino);

		void executa_Principal();
		void executa_SelecaoFase();
		//void executa_SelecaoMultiplayer();

		void carregar();


	public:
		
		Menu_Principal();
		~Menu_Principal();

		void executar();
};


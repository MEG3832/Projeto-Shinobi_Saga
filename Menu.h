#pragma once
#include "Ente.h"
#include "Fundo.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
class Jogo;
class Menu_Fase;

	class Menu : public Ente
	{
		protected:	// Mudei, pode?
			Jogo* pJog;
			Gerenciadores::Gerenciador_Grafico* GG;
			Gerenciadores::Gerenciador_de_Eventos* GE;
			Parallax::Fundo fundo;
			sf::Font fonte;
			std::vector<sf::Text> texto;
			int selecionado;
			bool executa;
			bool parar;

		public:
			Menu();
			~Menu();
			void executar();
			void inicializaFundo();	// Pensei em fazer um rand com os fundos de ambas as telas
			void inicializaTexto();
			void desenharTexto();
			void operator++();
			void operator--();
			void selecionar();
			void setJogo(Jogo* jogo);
	};


#pragma once
#include "Ente.h"
#include "Fundo.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
class Jogo;

	class Menu : public Ente
	{
		private:
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
			void inicializaFundo();	// Inicializa com o Japan Village
			void inicializaTexto();
			void desenharTexto();
			void operator++();
			void operator--();
			void selecionar();
			void setJogo(Jogo* jogo);
	};


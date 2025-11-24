#pragma once
#include "Ente.h"
#include "Fundo.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
class Jogo;
class Menu_Fase;

class Menu : public Ente
{
	protected:
		static Jogo* pJog;

		Gerenciadores::Gerenciador_de_Eventos* GE;

		sf::Font fonte;
		std::vector<sf::Text> texto;
		sf::Text titulo;

		int selecionado;
		bool parar;
		bool executa;

		Parallax::Fundo fundo;


		// Abstratas
		virtual void inicializaTexto() = 0;
		virtual void executar() = 0;

		void inicializaFundo();	// Pensei em fazer um rand com os fundos de ambas as telas
		void desenharTexto();

	public:
		Menu();
		virtual ~Menu();

		void selecionar();
		static void setJogo(Jogo* jogo);

		// Sobre cargas 
		void operator++();
		void operator--();
};


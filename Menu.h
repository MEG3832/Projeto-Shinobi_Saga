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
		static Entidades::Personagens::Jogador* pJog1;
		static Entidades::Personagens::Jogador* pJog2;
		Gerenciadores::Gerenciador_Grafico* GG;
		Gerenciadores::Gerenciador_de_Eventos* GE;
		sf::Font fonte;
		std::vector<sf::Text> texto;
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
		~Menu();

		void selecionar();
		static void setJogo(Jogo* jogo);
		static void setJogador1(Entidades::Personagens::Jogador* pJ);
		static void setJogador2(Entidades::Personagens::Jogador* pJ);

		// Sobre cargas 
		void operator++();
		void operator--();
};


#pragma once
// No momento, o jogo desenha 4 retangulos moveis e o fundo
#include "Fundo.h"
#include "ListaEntidades.h"
#include "Gerenciador_de_Eventos.h"
#include "Gerenciador_Colisoes.h"
#include "Plataforma.h"
#include "Redemoinho.h"

class Jogo {
	private:
		Gerenciadores::Gerenciador_Grafico* GG;	// Singelton
		Parallax::Fundo fundo;
		Entidades::Personagens::Jogador jogador;
		Gerenciadores::Gerenciador_de_Eventos* GE;	// Singleton
		Entidades::Personagens::Inimigo inimigo;
		Entidades::Obstaculos::Plataforma plataforma;
		Entidades::Obstaculos::Redemoinho redemoinho;
		Entidades::Projetil projetil;
		Gerenciadores::Gerenciador_Colisoes* GC1;	// Um para jogador, que tal?
		Listas::ListaEntidades lista_ents;

	public:
		Jogo();
		~Jogo();

		// Inicializacoes
		void inicializar();
		void inicializarGC();
		void inicializaListaEntidades();
		void inicializarListaInimigos();
		void inicializarListaObtaculos();
		void inicializarListaProjeteis();

		void executar();
};


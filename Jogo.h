#pragma once
#include "Fundo.h"
#include "ListaEntidades.h"
#include "Gerenciador_de_Eventos.h"
#include "Gerenciador_Colisoes.h"

class Jogo {
	private:
		Gerenciadores::Gerenciador_Grafico* GG;
		Parallax::Fundo fundo;
		Entidades::Personagens::Jogador jogador;
		Gerenciadores::Gerenciador_de_Eventos* GE;
		Entidades::Personagens::Inimigo inimigo;
		Entidades::Obstaculos::Obstaculo obstaculo;
		Entidades::Projetil projetil;
		Gerenciadores::Gerenciador_Colisoes* GC;
		Listas::ListaEntidades lista_ents;

	public:
		Jogo();
		~Jogo();
		void inicializar();
		void inicializaListaEntidades();
		void inicializarListaInimigos();
		void inicializarListaObtaculos();
		void inicializarListaProjeteis();
		void executar();
};


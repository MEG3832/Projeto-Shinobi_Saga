#pragma once
#include "Fundo.h"
#include "ListaEntidades.h"
#include "Gerenciador_de_Eventos.h"

class Jogo {
	private:
		Gerenciadores::Gerenciador_Grafico* GG;
		Parallax::Fundo fundo;
		Entidades::Personagens::Jogador jogador;
		Gerenciadores::Gerenciador_de_Eventos* GE;
		//Listas::ListaEntidades lista_ents;

	public:
		Jogo();
		~Jogo();
		void executar();
};


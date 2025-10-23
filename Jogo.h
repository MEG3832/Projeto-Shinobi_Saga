#pragma once
#include "Fundo.h"
#include "Header.h"
//#include "Jogador.h"
#include "ListaEntidades.h"
#include "Jogador.h"

class Jogo {
	private:
		Gerenciadores::Gerenciador_Grafico* GG;
		Parallax::Fundo fundo;
		Jogador jogador;
		//Listas::ListaEntidades lista_ents;

	public:
		Jogo();
		~Jogo();
		void executar();
};


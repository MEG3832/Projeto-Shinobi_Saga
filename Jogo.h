#pragma once
#include "Fundo.h"
#include "Header.h"
//#include "Jogador.h"
#include "ListaEntidades.h"
#include "Personagem.h"

class Jogo {
	private:
		Gerenciadores::Gerenciador_Grafico* GG;
		Parallax::Fundo fundo;
		Ente Figura;
		//Listas::ListaEntidades lista_ents;

	public:
		Jogo();
		~Jogo();
		void executar();
};


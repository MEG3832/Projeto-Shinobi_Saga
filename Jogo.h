#pragma once
#include "Fundo.h"
#include "Header.h"
#include "Ente.h"
#include "Jogador.h"

class Jogo {
	private:
		Gerenciadores::Gerenciador_Grafico* GG;
		Parallax::Fundo fundo;
		Ente Figura;

	public:
		Jogo();
		~Jogo();
		void executar();
};


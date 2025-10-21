#pragma once
#include "Fundo.h"
#include "Header.h"
#include "Ente.h"
#include "Jogador.h"

class Jogo {
	private:
		Gerenciador_Grafico* GG;
		Fundo fundo;
		Ente Figura;

	public:
		Jogo();
		~Jogo();
		void executar();
};


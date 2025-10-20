#pragma once
#include "Header.h"
#include "Fundo.h"

class Jogo {
	private:
		Gerenciador_Grafico* GG;
		Fundo* fundo;

	public:
		Jogo();
		~Jogo();
		void executar();
};


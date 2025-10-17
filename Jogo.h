#pragma once
#include "Header.h"
#include "Ente.h"

class Jogo {
	private:
		Gerenciador_Grafico* GG;
		Ente Figura;

	public:
		Jogo();
		~Jogo();
		void executar();
};


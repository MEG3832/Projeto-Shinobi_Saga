#pragma once
#include "Header.h"
#include "Gerenciador_Grafico.h"

class Jogo {
	private:
		Gerenciador_Grafico* GG;

	public:
		Jogo();
		~Jogo();
		void executar();
};


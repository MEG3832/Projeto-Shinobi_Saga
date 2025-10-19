#pragma once
#include "Camada.h"
#include "Ente.h"

class Fundo : public Ente
{
	private:
		Coord<float> posAnteriorCamera;
		std::vector<Camada*> camadas;

	public:
		Fundo();
		~Fundo();
		void desenhar();
		void addCamada(const char* caminhoTextura, const float v);
		void executar();
};


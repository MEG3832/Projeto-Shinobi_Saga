#pragma once
#include "Camada.h"
#include "Ente.h"

class Fundo : public Ente
{
	private:
		sf::Vector2f posAnteriorCamera;
		std::vector<Camada*> camadas;

	public:
		Fundo();
		~Fundo();
		void executar();
		void desenhar();
		void addCamada(const char* caminhoTextura, const float vel);
};


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
		void executar();	// Atualiza a posição de cada uma das camadas se houver velocidade e desenha elas
		void desenhar();
		void addCamada(const char* caminhoTextura, const float vel);
};


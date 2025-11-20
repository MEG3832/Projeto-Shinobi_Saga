#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Plataforma : public Obstaculo
		{
			private:	// Tirar altura e comprimento e colocar um atributo que individualize 
				int altura;
				int comprimento;
				sf::Texture textura;

			public:
				Plataforma(int id = 1);
				~Plataforma();
				void executar();
				void obstaculizar(Personagens::Jogador* p);
				void salvar();
				void salvarDataBuffer(nlohmann::json& buffer);
				void carregar(const nlohmann::json& j);
		};

	}

}
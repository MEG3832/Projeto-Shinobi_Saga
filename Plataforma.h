#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Plataforma : public Obstaculo
		{
			private:
				int altura;
				int comprimento;
				sf::Texture textura;

			public:
				Plataforma();
				~Plataforma();
				void executar();
				void obstaculizar(Personagens::Jogador* pJ);
				void salvar();
				void inicializaAnimacoes();
		};

	}

}
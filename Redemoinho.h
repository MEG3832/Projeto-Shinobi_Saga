#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Redemoinho : public Obstaculo
		{
			private:
				int altura;
				float largura;
				float danosidade;
				bool dano_unico;

			public:
				Redemoinho();
				~Redemoinho();
				void executar();
				void obstaculizar(Personagens::Jogador* p);
				void salvar();
				void inicializaAnimacoes();
				void atualizaAnimacao();
		};

	}

}
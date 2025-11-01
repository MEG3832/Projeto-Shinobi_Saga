#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Redemoinho : public Obstaculo
		{
			private:
				int altura;
				int comprimento;
				float dano;
				bool dano_unico;

			public:
				Redemoinho();
				~Redemoinho();
				void executar();
				void obstaculizar(Personagens::Jogador* pJ);
				void salvar();
				void inicializaAnimacoes();
				void atualizaAnimacao();
		};

	}

}
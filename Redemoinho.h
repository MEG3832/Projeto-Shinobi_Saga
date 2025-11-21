#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Redemoinho : public Obstaculo
		{
			private:
				float raio;
				float danosidade;

				// Variaveis
				bool dano_unico;

			public:
				Redemoinho();
				~Redemoinho();
				void executar();
				void obstaculizar(Personagens::Jogador* p);
				void salvar();
				void inicializaAnimacoes();
				void atualizaAnimacao();

				void salvarDataBuffer(nlohmann::json& buffer);
				void carregar(const nlohmann::json& j);
		};

	}

}
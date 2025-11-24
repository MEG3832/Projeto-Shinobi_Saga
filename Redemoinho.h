#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Obstaculos {

		class Redemoinho : public Obstaculo
		{
		private:
			const float raio;
			const float danosidade;

			// Variaveis
			bool dano_unico;


			void inicializaAnimacoes();
			void atualizaAnimacao();


		public:
			Redemoinho();
			~Redemoinho();

			void executar();
			void obstaculizar(Personagens::Jogador* p);

			void salvar();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);
		};

	}

}
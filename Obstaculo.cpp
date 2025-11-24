#include "Obstaculo.h"

namespace Entidades {

	namespace Obstaculos {

		Obstaculo::Obstaculo() :
			Entidade(),
			danoso(false)
		{}

		Obstaculo::~Obstaculo() 
		{
			danoso = false;
		}

		void Obstaculo::salvarDataBuffer(nlohmann::json& buffer) {

			Entidade::salvarDataBuffer(buffer);

			buffer["danoso"] = danoso;
		}

		void Obstaculo::carregar(const nlohmann::json& j) {
			try {
				danoso = j.at("danoso").get<bool>();
			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Chave 'fase' ausente." << e.what() << std::endl;
			}

			Entidade::carregar(j);
		}

		void Obstaculo::sofrerContraForca() {
			float aceleracao = -GRAVIDADE;
			veloc.y += aceleracao;
		}

	}

}
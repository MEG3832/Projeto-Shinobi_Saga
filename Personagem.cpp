#include "Personagem.h"

namespace Entidades {

	namespace Personagens {

		Personagem::Personagem() :
			Entidade(),
			num_vidas(0),
			dano(-1),
			paraEsq(false)
		{}

		Personagem::~Personagem()
		{
			num_vidas = -1;
			delete animador;
			animador = nullptr;
		}

		void Personagem::diminuiVida(float dano) {
			if (num_vidas - dano < 0) {
				num_vidas -= num_vidas;
			}
			else if (num_vidas > 0) {
				num_vidas -= dano;
			}
			std::cout << num_vidas << std::endl;
		}

		int Personagem::getVida()
		{
			return num_vidas;
		}

		int Personagem::getDano()
		{
			return dano;
		}

		void Personagem::salvarDataBuffer(nlohmann::json& buffer) {
			Entidade::salvarDataBuffer(buffer);

			buffer["num_vidas"] = num_vidas;
			buffer["dano"] = dano;
			buffer["paraEsq"] = paraEsq;
		}

		void Personagem::carregar(const nlohmann::json& j) {
			try {
				num_vidas = j.at("num_vidas").get<int>();
				dano = j.at("dano").get<float>();
				paraEsq = j.at("paraEsq").get<bool>();
			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Alguma das chaves estah ausente." << e.what() << std::endl;
			}

			Entidade::carregar(j);
		}

		void Personagem::setNoChao() {
			veloc.y = 0.0f;
		}

	}

}
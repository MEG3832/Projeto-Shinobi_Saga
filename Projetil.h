#pragma once
#include "Jogador.h"
#include "Kitsune.h"

namespace Entidades
{
	namespace Personagens
	{
		class Kitsune; // forward declaration
	}
}

namespace Entidades {

	class Projetil : public Entidade
	{
	protected:

		Personagens::Kitsune* pKitsune;

		// Variaveis
		bool ativo;


		void inicializaAnimacoes();
		void sofrerContraForca();


	public:
		Projetil(Personagens::Kitsune* pKits = nullptr);
		~Projetil();

		void setEstadoProj(bool estado);
		bool getEstadoProj();
		void setVelocidade(sf::Vector2f vel);
		void danificar(Personagens::Jogador* pJ);
		void executar();
		void salvar();
		void salvarDataBuffer(nlohmann::json& buffer);
		void carregar(const nlohmann::json& j);
	};

}
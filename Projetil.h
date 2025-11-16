#pragma once
#include "Entidade.h"
#include "Jogador.h"
//#include "Kitsune.h"

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
		bool ativo;
		Personagens::Kitsune* pKitsune;

	public:
		Projetil(Personagens::Kitsune* pKits);
		~Projetil();
		void setEstadoProj(bool estado);
		bool getEstadoProj();
		void setVelocidade(sf::Vector2f vel);
		void danificar(Personagens::Jogador* pJ);
		void executar();
		void salvar();

		void inicializaAnimacoes();
	};

}
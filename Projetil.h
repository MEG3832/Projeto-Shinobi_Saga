#pragma once
#include "Entidade.h"

namespace Entidades {

	class Projetil : public Entidade
	{
	protected:
		bool ativo;

	public:
		Projetil();
		~Projetil();
		void setEstadoProj(bool estado);
		bool getEstadoProj();
		void setVelocidade(sf::Vector2f vel);
		void danificar(Personagens::Jogador* pJ);
		void executar();
		void salvar();
	};

}
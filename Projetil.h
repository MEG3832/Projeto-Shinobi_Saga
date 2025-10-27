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
		void executar();
		void salvar();
	};

}
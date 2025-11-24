#pragma once
#include "Lista.h"
#include "Entidade.h"

namespace Listas {

	class ListaEntidades
	{
		private:
			Lista<Entidades::Entidade> LEs;

		public:
			ListaEntidades();
			~ListaEntidades();
			void incluir(Entidades::Entidade* pE);
			void remover(Entidades::Entidade* pE);	// Esta inutil, posso tirar?
			void limpar();
			void aplicarGravidade();
			void percorrer();
			void desenharEntidades();
			const int getSize() const;
			void salvar();
			void carregar();
	};

}

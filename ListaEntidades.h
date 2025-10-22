#pragma once
#include "Lista.h"
#include "Entidade.h"

namespace Listas {

	class ListaEntidades
	{
		private:
			Lista<Entidade> LEs;

		public:
			ListaEntidades();
			~ListaEntidades();
			void incluir(Entidade* PE);
			void remover(Entidade* PE);
			void percorrer();
	};

}

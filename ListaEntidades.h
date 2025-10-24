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
			void incluir(Entidades::Entidade* PE);
			void remover(Entidades::Entidade* PE);
			void percorrer();
	};

}

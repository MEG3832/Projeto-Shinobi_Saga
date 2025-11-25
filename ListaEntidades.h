/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

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

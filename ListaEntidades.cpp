#include "ListaEntidades.h"

namespace Listas {

	ListaEntidades::ListaEntidades() :
		LEs()
	{}

	ListaEntidades::~ListaEntidades() 
	{}

	void ListaEntidades::incluir(Entidade* PE) {
		if (PE) {
			LEs.incluir(PE);
		}
		else {
			std::cerr << "ERRO: Nao eh possivel incluir na lista um elemento NULL" << std::endl;
		}
	}

	void ListaEntidades::remover(Entidade* PE) {
		if (PE) {
			LEs.remover(PE);
		}
		else {
			std::cerr << "ERRO: Nao eh possivel remover da lista um elemento NULL" << std::endl;
		}
	}

	void ListaEntidades::percorrer() {
		for (int i = 0; i < LEs.getTam(); i++) {
			LEs[i]->executar();
		}
	}

}
#include "ListaEntidades.h"

namespace Listas {

	ListaEntidades::ListaEntidades() :
		LEs()
	{}

	ListaEntidades::~ListaEntidades() 
	{}

	void ListaEntidades::incluir(Entidades::Entidade* pE) {
		if (pE) {
			LEs.incluir(pE);
		}
		else {
			std::cerr << "ERRO: Nao eh possivel incluir na lista um elemento NULL" << std::endl;
		}
	}

	void ListaEntidades::remover(Entidades::Entidade* pE) {
		if (pE) {
			LEs.remover(pE);
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

	void ListaEntidades::desenharEntidades() {
		for (int i = 0; i < LEs.getTam(); i++) {
			LEs[i]->desenhar();
		}
	}

	const int ListaEntidades::getTam() const{
		return LEs.getTam();
	}

}
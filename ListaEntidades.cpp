#include "ListaEntidades.h"

namespace Listas {

	ListaEntidades::ListaEntidades() :
		LEs()
	{}

	ListaEntidades::~ListaEntidades() 
	{
	}

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

	void ListaEntidades::limpar() {
		LEs.limpar();
	}

	void ListaEntidades::percorrer() {
		for (int i = 0; i < LEs.getSize(); i++) {
			if (LEs[i]) {
				LEs[i]->executar();
			}
			else {
				std::cerr << "ERRO: Nao eh possivel executar pois a Entidade eh NULL" << std::endl;
			}
		}
	}

	void ListaEntidades::aplicarGravidade()
	{
		for (int i = 0; i < LEs.getSize(); i++) {
			if (LEs[i]) {
				LEs[i]->sofrerGravidade();
			}
			else {
				std::cerr << "ERRO: Nao eh possivel aplicar a gravidade pois a Entidade eh NULL" << std::endl;
			}
		}

	}

	void ListaEntidades::desenharEntidades() {
		for (int i = 0; i < LEs.getSize(); i++) {
			if (LEs[i]) {
				LEs[i]->desenhar();
			}
			else {
				std::cerr << "ERRO: Nao eh possivel desenhar a Entidade pois ela eh NULL" << std::endl;
			}
		}
	}

	const int ListaEntidades::getSize() const{
		return LEs.getSize();
	}

	void ListaEntidades::salvar() {
		for (int i = 0; i < LEs.getSize(); i++) {
			if (LEs[i]) {
				LEs[i]->salvar();
			}
			else {
				std::cerr << "ERRO: Nao eh possivel desenhar a Entidade pois ela eh NULL" << std::endl;
			}
		}
	}

}
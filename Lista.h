#pragma once

#include "Header.h"

namespace Listas {

	template <class TL>
	class Lista
	{
		private:

			template <class TE>
			class Elemento
			{
				private:
					Elemento<TE>* pProx;
					TE* pInfo;

				public:
					Elemento() : pProx(nullptr), pInfo(nullptr) {}
					~Elemento() { pProx = nullptr; delete pInfo;  pInfo = nullptr; }	// Esta certo deletar a informacao do elemento?
					void setInfo(TE* pt) { pInfo = pt; }
					void setProximo(Elemento<TE>* pE = nullptr) { pProx = pE; }
					Elemento<TE>* getProximo() const { return pProx; }
					TE* getInfo() const { return pInfo; }
			};

			Elemento<TL>* pPrimeiro;
			Elemento<TL>* pUltimo;
			int tamanho;

		public:

			Lista();
			~Lista();
			void incluir(TL* pt);	// Inclui ao final
			void limpar();	// Limpa toda a lista
			int getTam() const;
			void remover(TL* pE);	// Não delete o elemento, apenas o Elemento
			TL* operator[](int index);	// Acessa com [] como em vector

	};

	template <class TL>
	Lista<TL>::Lista() :
		pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0)
	{
	}

	template <class TL>
	Lista<TL>::~Lista()
	{
		limpar(); //limpa a lista por inteiro
	}

	template <class TL>
	void Lista<TL>::incluir(TL* pt)
	{
		if (pt) {
			Elemento<TL>* pElemAux = new Elemento<TL>;	// Coloquei aqui em cima para diminuir o número de verificações
			if (pElemAux) {
				if (pPrimeiro == nullptr && pUltimo == nullptr) //se a lista está vazia...
				{
					pElemAux->setInfo(pt);
					pElemAux->setProximo();	// Inclui NULL (parâmetro default)

					pPrimeiro = pElemAux;
					pUltimo = pElemAux;
				}

				else // a lista não está vazia, já há elementos dentro dela...
				{
					pElemAux->setInfo(pt);
					pElemAux->setProximo();

					pUltimo->setProximo(pElemAux);
					pUltimo = pElemAux;
				}
				tamanho++;
			}
			else {
				std::cerr << "ERRO: Nao foi possivel alocar um  novo Elemento" << std::endl;
			}
		}
		else {
			std::cerr << "ERRO: Nao eh possivel incluir na lista um elemento NULL" << std::endl;
		}
	}

	template <class TL>
	void Lista<TL>::limpar()
	{
		if (pPrimeiro != nullptr)
		{
			Elemento<TL>* pAux1 = pPrimeiro;
			Elemento<TL>* pAux2 = pAux1;

			while (pAux1 != nullptr)
			{
				pAux2 = pAux1->getProximo();
				delete (pAux1);
				pAux1 = pAux2;
			}

		}

		pPrimeiro = nullptr;
		pUltimo = nullptr;
		tamanho = 0;
	}

	template <class TL>
	int Lista<TL>::getTam() const
	{
		return tamanho;
	}

	template <class TL>
	void Lista<TL>::remover(TL* pE) {
		if (pPrimeiro) {
			if (pE) {
				Elemento<TL>* pAux1 = pPrimeiro;
				Elemento<TL>* pAux2 = nullptr;

				while (pAux1 && pAux1->getInfo() != pE) {
					pAux2 = pAux1;	// pAux2 só serve pra ficar no elemento anterior ao pAux1
					pAux1 = pAux1->getProximo();
				}

				if (pAux1) {
					if (pAux1->getInfo() == pE) { // Se o elemento realmente foi encontrado e não foi percorrida toda a lista sem achá-lo
						if (pPrimeiro == pAux1) {	// Se o elemento a ser removido é o primeiro da lista
							pAux2 = pAux1->getProximo();
							delete pAux1;
							pPrimeiro = pAux2;
						}
						else if (pUltimo == pAux1) {	// Se o elemento a ser removido é o último da lista
							delete pAux1;
							pUltimo = pAux2;
						}
						else { // Se o elemento a ser removido está da lista
							pAux2->setProximo(pAux1->getProximo());
							delete pAux1;
						}
						tamanho--;
					}
					else {
						std::cerr << "ERRO: Elemento a ser removido nao encontrado" << std::endl;
					}
				}
				else {
					std::cerr << "ERRO: Acesso invalido a lista" << std::endl;
				}

				pAux1 = nullptr;
				pAux2 = nullptr;
			}
			else {
				std::cerr << "ERRO: Elemento a ser removido eh NULL" << std::endl;
			}
		}
		else {
			std::cerr << "ERRO: Nao eh possivel remover pois a lista estah vazia" << std::endl;
		}
	}

	template <class TL>
	TL* Lista<TL>::operator[](int index) {	
		if(pPrimeiro) {
			if (index >= 0 && index < tamanho) {
				Elemento<TL>* pAux1 = pPrimeiro;
				for (int i = 0; i < index; i++) {
					pAux1 = pAux1->getProximo();
				}
				if(pAux1) {
					return pAux1->getInfo();
				}
				else {
					std::cerr << "ERRO: Acesso invalido da lista" << std::endl;
				}
			}
			else {
				std::cerr << "ERRO: Acesso invalido da lista" << std::endl;
			}
		}
		else {
			std::cerr << "ERRO: Nao eh possivel acessar um elemento da lista pois ela estah vazia" << std::endl;
		}
	}

}
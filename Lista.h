#pragma once

#include "Header.h"

#include "Elemento.h"

template <class TL>
class Lista
{
private:
	Elemento<TL>*  pPrimeiro;
	Elemento<TL>* pUltimo;
	int tamanho;

public:

	Lista():pPrimeiro(NULL), pUltimo(NULL), tamanho(0)
	{
	}

	~Lista()
	{
		limpar(); //limpa a lista por inteiro
	}

	void incluir(TL* pt)
	{
		if (pPrimeiro == NULL && pUltimo == NULL) //se a lista está vazia...
		{
			Elemento<TL>* pElemAux;

			pElemAux = new Elemento();
			
			if (pElemAux != NULL)
			{
				pElemAux->setInfo(pt);
				pElemAux->setProximo(NULL);

				pPrimeiro = pElemAux;
				pUltimo = pElemAux;
			}

		}

		else // a lista não está vazia, já há elementos dentro dela...
		{
			Elemento<TL>* pElemAux = new Elemento();

			if (pElemAux != NULL)
			{
				pElemAux->setInfo(pt);
				pElemAux->setProximo(NULL);

				pUltimo->setProximo(pElemAux);
				pUltimo = pElemAux;

			}

		}

		tamanho++;

	}

	void limpar()
	{
		if (pPrimeiro != NULL)
		{
			Elemento<TL>* pAux1;
			Elemento<TL>* pAux2;

			pAux1 = pPrimeiro;
			pAux2 = pAux1;

			while (pAux1 != NULL)
			{
				pAux2 = pAux1->getProximo();
				delete (pAux1);
				pAux1 = pAux2;
			}

		}

		pPrimeiro = NULL;
		pUltimo = NULL;
		tamanho = 0;
	}

	int getTam() const
	{
		return tamanho;
	}

	//...

	//fazer uma função que deleta apenas um elemento!! (será útil para inimigos e etc...)



};



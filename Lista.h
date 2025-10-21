#pragma once

#include "Header.h"

//#include "Elemento.h"

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
		limpar();
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
				pElemAux->setProx(NULL);

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
				pElemAux->setProx(NULL);

				pUltimo->setProx(pElemAux);
				pUltimo = pElemAux;

			}

		}

		tamanho++;

	}

	void limpar()
	{
		// TODO
	}

	int getTam()
	{
		return tamanho;
	}

	//...



};



#pragma once

#include "Header.h"

template <class TE>
class Elemento
{
private:

	Elemento <TE>* pProx;
	TE* pInfo;

public:

	Elemento():pProx(NULL), pInfo(NULL)
	{
	}

	~Elemento()
	{
		if (pInfo != NULL) {
			delete (pInfo);
			pInfo = NULL;
		}

		pProx = NULL;
	}

	void setInfo(TE* pt)
	{
		if (pt != NULL)
		{
			pInfo = pt;
		}
	}

	void setProximo(Elemento<TE>* pE)
	{
		pProx = pE;
	}

	Elemento<TE>* getProximo() const{ return pProx; }

};
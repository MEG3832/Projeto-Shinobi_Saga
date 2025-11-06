#include "Fase.h"

namespace Fases
{
	Fase::Fase() :
		maxTengus(10),
		chao(sf::RectangleShape(sf::Vector2f(9000,500))),
		lista_ents(),
		GC(&chao)
	{
		criarInimigos(); //virtual pura, desce para fase 1 ou 2
		criarObstaculos(); //virtual pura, desce para fase 1 ou 2
		criarCenario();
	}

	Fase::~Fase()
	{
		//...
	}

	void Fase::executar()
	{
		criarCenario();
		lista_ents.desenharEntidades();
		lista_ents.percorrer(); //percorre a lista chamando o executar de todas as entidades...
		GC.executar();
	}

	void Fase::criarCenario()
	{
		//como?
	}

	void Fase::criarTengus()
	{ //seria uma boa ideia passar como parametro a posicao em que ele vai nascer?

		const int min_tengus = 3;

		int qnt_inim = (rand() % (maxTengus - min_tengus + 1)) + min_tengus; //gera valor entre minimo e maximo definido

		for (int i = 0; i < qnt_inim; i++)
		{
			Entidades::Personagens::Tengu* pTengu;
			pTengu = new Entidades::Personagens::Tengu(); //temos que passar o endereço do jogador aqui...

			if (pTengu)
			{
				Entidades::Entidade* pEnt = static_cast<Entidades::Entidade*>(pTengu);
				lista_ents.incluir(pEnt);
				GC.incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(pTengu));
			}

			else
				std::cout << "Não foi possível alocar o Tengu!" << std::endl;

		}

	}

}
#include "Fase.h"

namespace Fases
{
	Fase::Fase() :
		chao(sf::RectangleShape(sf::Vector2f(9000,500)))
		lista_ents(),
		GC()
	{
		criarInimigos(); //virtual pura, desce para fase 1 ou 2
		criarObstaculos(); //virtual pura, desce para fase 1 ou 2
		criarCenario();
	}
}
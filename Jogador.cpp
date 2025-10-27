#include "Jogador.h"

namespace Entidades {

	namespace Personagens {

		Jogador::Jogador(const sf::Vector2f pos, int ident) :
			Personagem(),
			veloc(0.03f, 0.03f),
			pontos(0),
			id(ident),
			direcao()
		{
			corpo = new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
		}

		Jogador::Jogador() :
			Personagem(),
			veloc(0.03f, 0.03f),
			pontos(0),
			id(1),
			direcao()
		{
			corpo = new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
		}


		Jogador::~Jogador()
		{
			veloc.x = 0;
			veloc.y = 0;
			pontos = -1;
			id = 0;
		}

		const sf::RectangleShape* Jogador::getCorpo() {
			return corpo;
		}

		void colidir() {
			return;
		}

		void Jogador::executar()
		{
			return;
		}

		void Jogador::salvar()
		{
			return;
		}

		void Jogador::mover() {
			if (corpo) {
				if ('D' == direcao)
				{
					corpo->move(veloc.x, 0.0);
				}

				if ('C' == direcao)
				{
					corpo->move(0.0, -veloc.y);
				}

				if ('B' == direcao)
				{
					corpo->move(0.0, veloc.y);
				}

				if ('E' == direcao)
				{
					corpo->move(-veloc.x, 0.0);
				}
			}
			else {
				std::cerr << "ERRO: Nao foi possivel encontrar o corpo pois ele eh NULL" << std::endl;
			}
		}

		void Jogador::setDirecao(const char direcao) {
			this->direcao = direcao;
		}

	}

}
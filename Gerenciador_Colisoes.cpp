#include "Gerenciador_Colisoes.h"

namespace Gerenciadores {

	Gerenciador_Colisoes::Gerenciador_Colisoes() :
		LIs(),
		LOs(),
		LPs(),
		pJog1(nullptr)
	{}

	Gerenciador_Colisoes::~Gerenciador_Colisoes() {
		pJog1 = nullptr;
	}

	void Gerenciador_Colisoes::executar() {
		tratarColisoesJogsInimgs();

		tratarColisoesJogsObstacs();

		tratarColisoesJogsProjeteis();
	}

	void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
		if (pi) {
			LIs.incluir(static_cast<Entidades::Entidade*>(
						static_cast<Entidades::Personagens::Personagem*>(pi)));
		}
		else {
			std::cerr << "ERRO: nao eh possivel incluir o inimigo pois ele eh NULL" << std::endl;
		}
	}

	void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po) {
		if (po) {
			LOs.incluir(static_cast<Entidades::Entidade*>(po));
		}
		else {
			std::cerr << "ERRO: nao eh possivel incluir o obstaculo pois ele eh NULL" << std::endl;
		}
	}
	void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj) {
		if (pj) {
			LPs.incluir(static_cast<Entidades::Entidade*>(pj));
		}
		else {
			std::cerr << "ERRO: nao eh possivel incluir o projetil pois ele eh NULL" << std::endl;
		}
	}

	void Gerenciador_Colisoes::setJogador(Entidades::Personagens::Jogador* pJog) {
		pJog1 = pJog;
	}

	const bool Gerenciador_Colisoes::verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
		if (pe1) {
			if (pe2) {
				sf::Vector2f pos1 = pe1->getPos();
				sf::Vector2f pos2 = pe2->getPos();
				sf::Vector2f tam1 = pe1->getTam();
				sf::Vector2f tam2 = pe2->getTam();

				sf::Vector2f distanciaCentros(fabs((pos1.x + tam1.x / 2) - (pos2.x + tam2.x / 2)),
					fabs((pos1.y + tam1.y / 2) - (pos2.y + tam2.y / 2)));
				sf::Vector2f distanciaMinima((tam1.x / 2 + tam2.x / 2),
					(tam1.y / 2 + tam2.y / 2));
				sf::Vector2f ds((distanciaCentros.x - distanciaMinima.x),
					(distanciaCentros.y - distanciaMinima.y));

				return ((ds.x < 0.0f) && (ds.y < 0.0f));
			}
			else {
				std::cout << "ERRO: Nao foi possivel calcular a colisao pois ente 1 eh NULL" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "ERRO: Nao foi possivel calcular a colisao pois ente 1 eh NULL" << std::endl;
			return false;
		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
		if (pJog1) {
			for (int i = 0; i < LIs.getTam(); i++) {
				if (LIs.operator[](i)) {
					Entidades::Entidade* pE = static_cast<Entidades::Entidade*>(
						static_cast<Entidades::Personagens::Personagem*>(LIs.operator[](i)));
					if (verificaColisao(pJog1, pE)) {
						pJog1->colidir(pE);
					}
				}
				else {
					std::cerr << "ERRO: nao eh possivel calcular a colisao pois o inimigo eh NULL" << std::endl;
				}
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o jogador eh NULL" << std::endl;
		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
		if (pJog1) {
			for (int i = 0; i < LOs.getTam(); i++) {
				if (LOs.operator[](i)) {
					Entidades::Entidade* pE = static_cast<Entidades::Entidade*>(LOs.operator[](i));
					if (verificaColisao(pJog1, pE)) {
						pJog1->colidir(pE);
					}
				}
				else {
					std::cerr << "ERRO: nao eh possivel calcular a colisao pois o inimigo eh NULL" << std::endl;
				}
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o jogador eh NULL" << std::endl;
		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
		if (pJog1) {
			for (int i = 0; i < LPs.getTam(); i++) {
				if (LPs.operator[](i)) {
					Entidades::Entidade* pE = static_cast<Entidades::Entidade*>(LPs.operator[](i));
					if (verificaColisao(pJog1, pE)) {
						pJog1->colidir(pE);
					}
				}
				else {
					std::cerr << "ERRO: nao eh possivel calcular a colisao pois o inimigo eh NULL" << std::endl;
				}
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o jogador eh NULL" << std::endl;
		}
	}


}
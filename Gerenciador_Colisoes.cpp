#include "Gerenciador_Colisoes.h"

namespace Gerenciadores {

	Gerenciador_Colisoes* Gerenciador_Colisoes::pColisoes = nullptr;

	Gerenciador_Colisoes::Gerenciador_Colisoes(sf::RectangleShape* piso) :
		LIs(),
		LOs(),
		LPs(),
		pJog1(nullptr),
		chao(piso)
	{}

	Gerenciador_Colisoes::~Gerenciador_Colisoes() {
		pJog1 = nullptr;
	}

	Gerenciador_Colisoes* Gerenciador_Colisoes::getGerenciadorColisoes(sf::RectangleShape* piso) {
		if (!pColisoes) {
			pColisoes = new Gerenciador_Colisoes(piso);
		}

		return pColisoes;
	}

	void Gerenciador_Colisoes::executar() {
		tratarColisoesJogsInimgs();

		tratarColisoesJogsObstacs();

		tratarColisoesJogsProjeteis();

		tratarColisoesJogsChao();
	}

	void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
		if (pi) {
			LIs.push_back(pi);
		}
		else {
			std::cerr << "ERRO: nao eh possivel incluir o inimigo pois ele eh NULL" << std::endl;
		}
	}

	void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po) {
		if (po) {
			LOs.push_back(po);
		}
		else {
			std::cerr << "ERRO: nao eh possivel incluir o obstaculo pois ele eh NULL" << std::endl;
		}
	}
	void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj) {
		if (pj) {
			LPs.insert(pj);
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

	const bool Gerenciador_Colisoes::verificaColisaoChao(Entidades::Entidade* pe) const {
		if (pe) {
			if (chao) {
				sf::Vector2f pos1 = pe->getPos();
				sf::Vector2f pos2 = chao->getPosition();
				sf::Vector2f tam1 = pe->getTam();
				sf::Vector2f tam2 = chao->getSize();

				sf::Vector2f distanciaCentros(fabs((pos1.x + tam1.x / 2) - (pos2.x + tam2.x / 2)),
					fabs((pos1.y + tam1.y / 2) - (pos2.y + tam2.y / 2)));
				sf::Vector2f distanciaMinima((tam1.x / 2 + tam2.x / 2),
					(tam1.y / 2 + tam2.y / 2));
				sf::Vector2f ds((distanciaCentros.x - distanciaMinima.x),
					(distanciaCentros.y - distanciaMinima.y));

				return ((ds.x < 0.0f) && (ds.y < 0.0f));
			}
			else {
				std::cout << "ERRO: Nao foi possivel calcular a colisao pois ente 2 eh NULL" << std::endl;
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
			for (int i = 0; i < (int)LIs.size(); i++) {
				if (LIs[i]) {
					//Entidades::Entidade* pI = static_cast<Entidades::Entidade*>(
											  //static_cast<Entidades::Personagens::Personagem*>(LIs[i]));
					if (verificaColisao(pJog1, LIs[i])) {
						pJog1->colidir(LIs[i]);
						if (LIs[i]->getIntransponivel()) {
							reposicionar(pJog1->getCorpo(), LIs[i]->getCorpo());
						}
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
			std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin();
			for (it = LOs.begin(); it != LOs.end(); it++) {
				if (*it) {
					Entidades::Entidade* pO = static_cast<Entidades::Entidade*>(*it);
					if (verificaColisao(pJog1, pO)) {
						if ((*it)->getIntransponivel()) {
							reposicionar(pJog1->getCorpo(), pO->getCorpo());
						}
						(*it)->obstaculizar(pJog1);
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
			std::set<Entidades::Projetil*>::iterator it = LPs.begin();
			for (it = LPs.begin(); it != LPs.end(); it++) {
				if (*it) {
					Entidades::Entidade* pP = static_cast<Entidades::Entidade*>(*it);
					if (verificaColisao(pJog1, pP)) {
						if ((*it)->getIntransponivel()) {
							reposicionar(pJog1->getCorpo(), pP->getCorpo());
						}
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

	void Gerenciador_Colisoes::tratarColisoesJogsChao() {
		if (pJog1) {
			if (chao) {
				if (verificaColisaoChao(pJog1)) {
					reposicionar(pJog1->getCorpo(), chao);
				}
			}
			else {
				std::cerr << "ERRO: nao eh possivel calcular a colisao pois o chao eh NULL" << std::endl;
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o jogador eh NULL" << std::endl;
		}
	}

	void Gerenciador_Colisoes::reposicionar(sf::RectangleShape* c1, sf::RectangleShape* c2) {
		if (c1) {
			if (c2) {
				sf::Vector2f pos1 = c1->getPosition();
				sf::Vector2f pos2 = c2->getPosition();
				sf::Vector2f tam1 = c1->getSize();
				sf::Vector2f tam2 = c2->getSize();

				sf::Vector2f distanciaCentros((pos2.x + tam2.x / 2) - (pos1.x + tam1.x / 2),
											  (pos2.y + tam2.y / 2) - (pos1.y + tam1.y / 2));
				sf::Vector2f distanciaMinima((tam1.x / 2 + tam2.x / 2),
											 (tam1.y / 2 + tam2.y / 2));
				sf::Vector2f ds((distanciaCentros.x),
								(distanciaCentros.y));
				if(distanciaCentros.x > 0) {
					ds.x -= distanciaMinima.x;
				}
				else {
					ds.x += distanciaMinima.x;
				}
				if (distanciaCentros.y > 0) {
					ds.y -= distanciaMinima.y;
				}
				else {
					ds.y += distanciaMinima.y;
				}

				if(c2 == chao) {
					c1->move(0.0f, ds.y);
				}
				else {
					if (abs(ds.x) < abs(ds.y)) {
						c1->move(ds.x, 0.0f);
					}
					else {
						c1->move(0.0f, ds.y);
					}
				}
			}
			else {
				std::cout << "ERRO: Nao foi possivel calcular a colisao pois corpo 2 eh NULL" << std::endl;
			}
		}
		else {
			std::cout << "ERRO: Nao foi possivel calcular a colisao pois corpo 1 eh NULL" << std::endl;
		}
	}

}
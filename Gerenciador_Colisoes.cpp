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

	Gerenciador_Colisoes* Gerenciador_Colisoes::getGerenciadorColisoes() {
		if (!pColisoes) {
			pColisoes = new Gerenciador_Colisoes(nullptr);
		}

		return pColisoes;
	}

	void Gerenciador_Colisoes::executar() {
		if (pJog1) {
			if (pJog1->getHitBox()) {
				tratarColisoesJogsInimgs();

				tratarColisoesJogsObstacs();

				tratarColisoesJogsProjeteis();

				tratarColisoesJogsChao();
			}
			else {
				std::cerr << "ERRO: nao eh possivel calcular a colisao pois o Hit Box eh NULL" << std::endl;
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o jogador eh NULL" << std::endl;
		}
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

	//esse verificaColisao tem o intuito da verificação entre colisão corpo-a-corpo entre as entidades.
	//aqui usamos as hitboxes principais!!
	const bool Gerenciador_Colisoes::verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
		if (pe1) {
			if (pe2) {
				sf::Vector2f pos1 = pe1->getHitBox()->getPosition();
				sf::Vector2f pos2 = pe2->getHitBox()->getPosition();
				sf::Vector2f tam1 = pe1->getHitBox()->getSize();
				sf::Vector2f tam2 = pe2->getHitBox()->getSize();

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

	//já essa aqui, verifica colisões mais específicas, entre retângulos. Usamos para o hitbox de ataque vs hitbox do inimigo.
	const bool Gerenciador_Colisoes::verificaColisao(sf::RectangleShape* r1, sf::RectangleShape* r2) const {
		if (r1 && r2) {
			sf::FloatRect rect1 = r1->getGlobalBounds();
			sf::FloatRect rect2 = r2->getGlobalBounds();
			return rect1.intersects(rect2);
		}
		return false;
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
		for (int i = 0; i < (int)LIs.size(); i++) {

			if (LIs[i] && !LIs[i]->getEstaMorto()) {

				if (pJog1->getHitboxAtaqueAtiva()) {

					if (verificaColisao(pJog1->getHitboxAtaque(), LIs[i]->getHitBox())) {
						LIs[i]->diminuiVida(pJog1->getDano());
					}
				}

				if (verificaColisao((static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Personagens::Personagem*>(pJog1))),
					(static_cast<Entidades::Entidade*>(
						static_cast<Entidades::Personagens::Personagem*>(LIs[i]))))) {

					if (!pJog1->getAtacando() && !LIs[i]->getAtordoado()) {
						pJog1->colidir(LIs[i]);
					}

					if (LIs[i]->getIntransponivel()) {
						reposicionar(pJog1->getHitBox(), LIs[i]->getHitBox());
					}
				}
			}
						
			else {
				std::cerr << "ERRO: nao eh possivel calcular a colisao pois o inimigo eh NULL" << std::endl;
			}
		}
	}
	
	void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
		std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin();
		for (it = LOs.begin(); it != LOs.end(); it++) {

			if (*it) {

				Entidades::Entidade* pO = static_cast<Entidades::Entidade*>(*it);

				if (verificaColisao(static_cast<Entidades::Entidade*>(

					static_cast<Entidades::Personagens::Personagem*>(pJog1)),
					(static_cast<Entidades::Entidade*>(pO)))) {

					if ((*it)->getIntransponivel()) {
						reposicionar(pJog1->getHitBox(), pO->getHitBox());

						if (pJog1->getCorpo()) {

							pJog1->getCorpo()->setPosition(
								pJog1->getHitBox()->getPosition().x - (pJog1->getCorpo()->getSize().x / 2 - pJog1->getHitBox()->getSize().x / 2),
								pJog1->getHitBox()->getPosition().y);
						}
						else {
							std::cerr << "ERRO: nao eh possivel reposicionar pois o corpo eh NULL" << std::endl;
						}
					}
					(*it)->obstaculizar(pJog1);
				}
			}
			else {
				std::cerr << "ERRO: nao eh possivel calcular a colisao pois o obstaculo eh NULL" << std::endl;
			}
		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
		std::set<Entidades::Projetil*>::iterator it = LPs.begin();
		for (it = LPs.begin(); it != LPs.end(); it++) {
			if (*it) {

				if (!(*it)->getEstadoProj()) {
					continue; // ignora este projétil, já que ele está inativo.
				}

				Entidades::Entidade* pP = static_cast<Entidades::Entidade*>(*it);
				if (verificaColisao(static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Personagens::Personagem*>(pJog1)),
					(static_cast<Entidades::Entidade*>(pP)))) {
					//adicionei isso:

					(*it)->danificar(pJog1);

					if ((*it)->getIntransponivel()) {
						reposicionar(pJog1->getCorpo(), pP->getCorpo());
					}
				}
			}
			else {
				std::cerr << "ERRO: nao eh possivel calcular a colisao pois o projetil eh NULL" << std::endl;
			}
		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsChao() {
		if (chao) {
			if (verificaColisaoChao(pJog1)) {
				reposicionar(pJog1->getHitBox(), chao);
				pJog1->setNoChao();
				if (pJog1->getCorpo()) {
					pJog1->getCorpo()->setPosition(
						pJog1->getHitBox()->getPosition().x - (pJog1->getCorpo()->getSize().x / 2 - pJog1->getHitBox()->getSize().x / 2),
						pJog1->getHitBox()->getPosition().y);
				}
				else {
					std::cerr << "ERRO: nao eh possivel reposicionar pois o corpo eh NULL" << std::endl;
				}
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o chao eh NULL" << std::endl;
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

	void Gerenciador_Colisoes::setChao(sf::RectangleShape* piso) {
		chao = piso;
	}

}
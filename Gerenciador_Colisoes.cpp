	#include "Gerenciador_Colisoes.h"

namespace Gerenciadores {

	Gerenciador_Colisoes* Gerenciador_Colisoes::pColisoes = nullptr;

	Gerenciador_Colisoes::Gerenciador_Colisoes(sf::RectangleShape* piso) :
		LIs(),
		LOs(),
		LPs(),
		pJog1(nullptr),
		chao(piso)
	{
	}

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

		tratarColisoesInimigosChao();

		tratarColisoesInimigosObstacs();

		tratarColisoesObstacsChao();

		tratarColisaoObstacsObstacs();

		tratarColisaoInimgInimig();
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
				if (pe->getCorpo()->getPosition().y + pe->getCorpo()->getSize().y >= ALTURA_TELA - chao->getSize().y) {
					return true;
				}
				else {
					return false;
				}
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

				if (pJog1->getAtacando()) {

					if (verificaColisao(pJog1->getHitboxAtaque(), LIs[i]->getHitBox())) {
						LIs[i]->diminuiVida(pJog1->getDano());
					}
				}

				if (verificaColisao((static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Personagens::Personagem*>(pJog1))),
					(static_cast<Entidades::Entidade*>(
						static_cast<Entidades::Personagens::Personagem*>(
							static_cast<Entidades::Personagens::Inimigo*>(LIs[i])))))) {

					if (!pJog1->getAtacando() && !LIs[i]->getAtordoado()) {
						pJog1->colidir(LIs[i]);
					}

					if (LIs[i]->getIntransponivel()) {
						reposicionar(pJog1->getHitBox(), LIs[i]->getHitBox());
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
				Entidades::Entidade* pP = static_cast<Entidades::Entidade*>(*it);
				if (verificaColisao(static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Personagens::Personagem*>(pJog1)),
					(static_cast<Entidades::Entidade*>(pP)))) {
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
					pJog1->getCorpo()->setPosition(pJog1->getCorpo()->getPosition().x,
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

	void Gerenciador_Colisoes::tratarColisoesInimigosChao() {
		if (!chao) {
			std::cerr << "ERRO: nao eh possivel calcular a colisao (Inimigos-Chao) pois o chao eh NULL" << std::endl;
			return;
		}

		for (int i = 0; i < (int)LIs.size(); i++) {
			if (LIs[i]) {
				if (verificaColisaoChao(LIs[i])) {
					reposicionar(LIs[i]->getHitBox(), chao);
					LIs[i]->setNoChao();

					if (LIs[i]->getCorpo()) {
						LIs[i]->getCorpo()->setPosition(
							LIs[i]->getHitBox()->getPosition().x - (LIs[i]->getCorpo()->getSize().x / 2 - LIs[i]->getHitBox()->getSize().x / 2),
							LIs[i]->getHitBox()->getPosition().y
						);
					}
				}
			}
		}
	}

	void Gerenciador_Colisoes::tratarColisoesInimigosObstacs() { //comparamos cada inimigo com cada obstáculo

		for (int i = 0; i < (int)LIs.size(); i++) {

			Entidades::Personagens::Inimigo* pInimigo = LIs[i];

			// ignora inimigos nulos ou que já estão mortos
			if (!pInimigo || pInimigo->getEstaMorto()) {
				continue;
			}

			// Loop 2: Passa por toda a lista de Obstáculos (LOs)
			std::list<Entidades::Obstaculos::Obstaculo*>::iterator it_obs = LOs.begin();
			for (it_obs = LOs.begin(); it_obs != LOs.end(); it_obs++) {

				Entidades::Obstaculos::Obstaculo* pObstaculo = *it_obs;

				// ignora obstáculos nulos
				if (!pObstaculo) {
					continue;
				}

				// converte para Entidade* para usar a função de verificação
				Entidades::Entidade* pE_Inimigo = static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Personagens::Personagem*>(
						static_cast<Entidades::Personagens::Inimigo*>(pInimigo)));
				Entidades::Entidade* pE_Obstaculo = static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Obstaculos::Obstaculo*>(pObstaculo));

				// se houver colisão...
				if (verificaColisao(pE_Inimigo, pE_Obstaculo)) {

					// se o obstáculo for "sólido" (intransponível)...
					if (pObstaculo->getIntransponivel()) {

						// reposiciona a hitbox do inimigo
						reposicionar(pInimigo->getHitBox(), pE_Obstaculo->getHitBox());
						pInimigo->setNoChao();

						// reposiciona o corpo visual do inimigo (baseado na hitbox)
						if (pInimigo->getCorpo()) {
							pInimigo->getCorpo()->setPosition(
								pInimigo->getHitBox()->getPosition().x - (pInimigo->getCorpo()->getSize().x / 2 - pInimigo->getHitBox()->getSize().x / 2),
								pInimigo->getHitBox()->getPosition().y
							);
						}
					}

				}
			}
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
				if (distanciaCentros.x > 0) {
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

				if (c2 == chao) {
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

	void Gerenciador_Colisoes::tratarColisoesObstacsChao() {
		if (!chao) {
			std::cerr << "ERRO: nao eh possivel calcular a colisao (Inimigos-Chao) pois o chao eh NULL" << std::endl;
			return;
		}


		std::list<Entidades::Obstaculos::Obstaculo*>::iterator it_obs = LOs.begin();
		for (it_obs = LOs.begin(); it_obs != LOs.end(); it_obs++) {

			Entidades::Obstaculos::Obstaculo* pObstaculo = *it_obs;

			if (pObstaculo) {
				// converte para Entidade* para usar a função de verificação
				Entidades::Entidade* pE_Obstaculo = static_cast<Entidades::Entidade*>(
					static_cast<Entidades::Obstaculos::Obstaculo*>(pObstaculo));

				if (verificaColisaoChao(pObstaculo)) {
					reposicionar(pObstaculo->getHitBox(), chao);

					if (pObstaculo->getCorpo()) {
						pObstaculo->getCorpo()->setPosition(
							pObstaculo->getHitBox()->getPosition().x - (pObstaculo->getCorpo()->getSize().x / 2 - pObstaculo->getHitBox()->getSize().x / 2),
							pObstaculo->getHitBox()->getPosition().y
						);
					}
				}
			}
		}
	}

	void Gerenciador_Colisoes::setChao(sf::RectangleShape* piso) {
		chao = piso;
	}

	void Gerenciador_Colisoes::tratarColisaoObstacsObstacs() {
		std::list<Entidades::Obstaculos::Obstaculo*>::iterator it1_obs = LOs.begin();
		std::list<Entidades::Obstaculos::Obstaculo*>::iterator it2_obs = LOs.begin();

		for (it1_obs = LOs.begin(); it1_obs != LOs.end(); it1_obs++) {
			Entidades::Obstaculos::Obstaculo* pObstaculo1 = *it1_obs;

			if (pObstaculo1) {

				std::list<Entidades::Obstaculos::Obstaculo*>::iterator tmp = it1_obs;

				for (it2_obs = ++tmp; it2_obs != LOs.end(); it2_obs++) {
					Entidades::Obstaculos::Obstaculo* pObstaculo2 = *it2_obs;

					if (pObstaculo2) {

						// converte para Entidade* para usar a função de verificação
						Entidades::Entidade* pE_Obstaculo1 = static_cast<Entidades::Entidade*>(
							static_cast<Entidades::Obstaculos::Obstaculo*>(pObstaculo1));
						Entidades::Entidade* pE_Obstaculo2 = static_cast<Entidades::Entidade*>(
							static_cast<Entidades::Obstaculos::Obstaculo*>(pObstaculo2));

						if (verificaColisao(pE_Obstaculo1, pE_Obstaculo2)) {
							reposicionar(pObstaculo1->getHitBox(), pObstaculo2->getHitBox());

							if (pObstaculo1->getCorpo()) {
								pObstaculo1->getCorpo()->setPosition(
									pObstaculo1->getHitBox()->getPosition().x - (pObstaculo1->getCorpo()->getSize().x / 2 - pObstaculo1->getHitBox()->getSize().x / 2),
									pObstaculo1->getHitBox()->getPosition().y
								);
							}
						}
					}
				}
			}
		}
	}

	bool Gerenciador_Colisoes::verificaColisaoEnteObstacs(Entidades::Entidade* pE) {
		if (pE) {
			if (!LOs.empty()) {
				std::list<Entidades::Obstaculos::Obstaculo*>::iterator it_obs = LOs.begin();
				for (it_obs = LOs.begin(); it_obs != LOs.end(); it_obs++) {

					Entidades::Obstaculos::Obstaculo* pObstaculo = *it_obs;

					// ignora obstáculos nulos
					if (pObstaculo) {
						if (verificaColisao(pE, static_cast<Entidades::Obstaculos::Obstaculo*>(
							static_cast<Entidades::Entidade*>(pObstaculo)))) {
							return true;
						}
					}
					else {
						std::cout << "ERRO: Nao eh possivel verificar a colisao pois o obstaculo eh NULL" << std::endl;
					}
				}
			}
			return false;
		}
		else {
			std::cout << "ERRO: Nao eh possivel verificar a colisao pois a entidade eh NULL" << std::endl;
		}
	}

	bool Gerenciador_Colisoes::verificaColisaoEnteInimgs(Entidades::Entidade* pE) {
		for (int i = 0; i < (int)LIs.size(); i++) {

			Entidades::Personagens::Inimigo* pInimigo = LIs[i];

			// ignora inimigos nulos ou que já estão mortos
			if (!pInimigo || pInimigo->getEstaMorto()) {
				continue;
			}	

			// converte para Entidade* para usar a função de verificação
			Entidades::Entidade* pE_Inimigo = static_cast<Entidades::Entidade*>(
											  static_cast<Entidades::Personagens::Personagem*>(
											  static_cast<Entidades::Personagens::Inimigo*>(pInimigo)));

			// se houver colisão...
			if (verificaColisao(pE, pE_Inimigo)) {
				return true;
			}
		}
		return false;
	}

	void Gerenciador_Colisoes::tratarColisaoInimgInimig() {
		for (int i = 0; i < (int)LIs.size(); i++) {

			Entidades::Personagens::Inimigo* pInimigo1 = LIs[i];

			// ignora inimigos nulos ou que já estão mortos
			if (!pInimigo1 || pInimigo1->getEstaMorto()) {
				continue;
			}

			for (int j = i + 1; j < (int)LIs.size(); j++) {

				Entidades::Personagens::Inimigo* pInimigo2 = LIs[j];

				// ignora inimigos nulos ou que já estão mortos
				if (!pInimigo2 || pInimigo2->getEstaMorto()) {
					continue;
				}

				// converte para Entidade* para usar a função de verificação
				Entidades::Entidade* pE_Inimigo1 = static_cast<Entidades::Entidade*>(
												   static_cast<Entidades::Personagens::Personagem*>(
											  	   static_cast<Entidades::Personagens::Inimigo*>(pInimigo1)));
				Entidades::Entidade* pE_Inimigo2 = static_cast<Entidades::Entidade*>(
												   static_cast<Entidades::Personagens::Personagem*>(
												   static_cast<Entidades::Personagens::Inimigo*>(pInimigo2)));

				// se houver colisão...
				if (verificaColisao(pE_Inimigo1, pE_Inimigo2)) {

					// reposiciona a hitbox do inimigo
					reposicionar(pInimigo1->getHitBox(), pE_Inimigo2->getHitBox());
					pInimigo1->setNoChao();

					// reposiciona o corpo visual do inimigo (baseado na hitbox)
					if (pInimigo1->getCorpo()) {
						pInimigo1->getCorpo()->setPosition(
							pInimigo1->getHitBox()->getPosition().x - (pInimigo1->getCorpo()->getSize().x / 2 - pInimigo1->getHitBox()->getSize().x / 2),
							pInimigo1->getHitBox()->getPosition().y
						);
					}
				}
			}
		}
	}
}
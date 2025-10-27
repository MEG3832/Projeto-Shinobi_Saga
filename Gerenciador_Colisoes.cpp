#include "Gerenciador_Colisoes.h"

namespace Gerenciadores {

	Gerenciador_Colisoes* Gerenciador_Colisoes::pColisoes = nullptr;

	Gerenciador_Colisoes::Gerenciador_Colisoes(Entidades::Personagens::Jogador* pJog) :
		LIs(),
		LOs(),
		LPs(),
		pJog1(pJog)
	{}

	const bool Gerenciador_Colisoes::verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
		return false;
	}

	void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
		if (pJog1) {
			for (int i = 0; i < LIs.getTam(); i++) {
				if (LIs.operator[](i)) {
					verificaColisao(pJog1, static_cast<Entidades::Entidade*>(
									static_cast<Entidades::Personagens::Personagem*>(LIs.operator[](i))));
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
					verificaColisao(pJog1, static_cast<Entidades::Entidade*>(LOs.operator[](i)));
				}
				else {
					std::cerr << "ERRO: nao eh possivel calcular a colisao pois o objeto eh NULL" << std::endl;
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
						verificaColisao(pJog1, static_cast<Entidades::Entidade*>(LPs.operator[](i)));
				}
				else {
					std::cerr << "ERRO: nao eh possivel calcular a colisao pois o projetil eh NULL" << std::endl;
				}
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel calcular a colisao pois o jogador eh NULL" << std::endl;
		}
	}

	Gerenciador_Colisoes::~Gerenciador_Colisoes() {
		pJog1 = nullptr;
	}

	// Padrão de Projeto Singleton
	Gerenciador_Colisoes* Gerenciador_Colisoes::getGerenciadorColisoes(Entidades::Personagens::Jogador* pJog) {
		if (!pColisoes) {
			pColisoes = new Gerenciador_Colisoes();
		}

		return pColisoes;
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



}
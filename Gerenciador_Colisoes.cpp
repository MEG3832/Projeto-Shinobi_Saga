#include "Gerenciador_Colisoes.h"

namespace Gerenciadores {

	Gerenciador_Colisoes* Gerenciador_Colisoes::pColisoes = nullptr;

	Gerenciador_Colisoes::Gerenciador_Colisoes(Entidades::Personagens::Jogador* pJog,
											   Listas::Lista<Entidades::Personagens::Inimigo*>* Inimigos,
											   Listas::Lista<Entidades::Obstaculo*>* Obstaculos,
											   Listas::Lista<Entidades::Projetil*>* Projeteis) :
		LIs(Inimigos),
		LOs(Obstaculos),
		LPs(Projeteis),
		pJog1(pJog)
	{}

	const bool Gerenciador_Colisoes::verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {

	}

	void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
		for (int i = 0; i < LIs->getTamanho(); i++ {

		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {

	}

	void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {

	}

	Gerenciador_Colisoes::~Gerenciador_Colisoes() {
		LIs = nullptr;
		LOs = nullptr;
		LPs = nullptr;
		pJog1 = nullptr;
	}

	// Padrão de Projeto Singleton
	Gerenciador_Colisoes* Gerenciador_Colisoes::getGerenciadorColisoes(Entidades::Personagens::Jogador pJog) {
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

	void Gerenciador_Colisoes::setListaInimigos(Listas::Lista<Entidades::Personagens::Inimigo*>* Inimigos) {
		LIs = Inimigos;
	}

	void Gerenciador_Colisoes::setListaObstaculos(Listas::Lista<Entidades::Obstaculo*>* Obstaculos) {
		LOs = Obstaculos;
	}

	void Gerenciador_Colisoes::setListaProjeteis(Listas::Lista<Entidades::Projetil*>* Projeteis) {
		LPs = Projeteis;
	}



}
#pragma once
#include "Lista.h"
#include "Obstaculo.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "Jogador.h"

namespace Gerenciadores {

	class Gerenciador_Colisoes
	{
		private:
			// Listas (não pode usar a Lista template que eu fiz?)
			// Só o gerenciador de colisoes que precisa separar a lista em inimigos, obstaculos e projeteis? Se não, acho melhor referenciar as listas do Jogo
			Listas::Lista<Entidades::Entidade> LIs;
			Listas::Lista<Entidades::Entidade> LOs;
			Listas::Lista<Entidades::Entidade> LPs;
			Entidades::Personagens::Jogador* pJog1;

			// Funções privadas de verificação de colisão
			const bool verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
			void tratarColisoesJogsInimgs();
			void tratarColisoesJogsObstacs();
			void tratarColisoesJogsProjeteis();

		public:
			Gerenciador_Colisoes();
			~Gerenciador_Colisoes();
			void executar();
			void incluirInimigo(Entidades::Personagens::Inimigo* pi);
			void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
			void incluirProjetil(Entidades::Projetil* pj);
			void setJogador(Entidades::Personagens::Jogador* pJog);
	};

}


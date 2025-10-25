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
			// Sóo gerenciador de colisoes que precisa separar a lista em inimigos, obstaculos e projeteis? Se não, acho melhor referenciar as listas do Jogo
			Listas::Lista<Entidades::Personagens::Inimigo*>* LIs;
			Listas::Lista<Entidades::Obstaculo::Obstaculo*>* LOs;
			Listas::Lista<Entidades::Projetil*>* LPs;
			Entidades::Personagens::Jogador* pJog1;

			// Padrão de Projéto Singleton
			static Gerenciador_Colisoes* pColisoes;
			Gerenciador_Colisoes(Entidades::Personagens::Jogador* pJog = nullptr,
								 Listas::Lista<Entidades::Personagens::Inimigo*>* Inimigos = nullptr,
								 Listas::Lista<Entidades::Obstaculo*>* Obstaculos = nullptr,
								 Listas::Lista<Entidades::Projetil*>* Projeteis = nullptr);

			// Funções privadas de verificação de colisão
			const bool verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
			void tratarColisoesJogsInimgs();
			void tratarColisoesJogsObstacs();
			void tratarColisoesJogsProjeteis();

		public:
			~Gerenciador_Colisoes();
			Gerenciador_Colisoes* getGerenciadorColisoes(Entidades::Personagens::Jogador pJog);
			void executar();
			void setListaInimigos(Listas::Lista<Entidades::Personagens::Inimigo*>* LIs);
			void setListaObstaculos(Listas::Lista<Entidades::Obstaculo*>* LOs);
			void setListaProjeteis(Listas::Lista<Entidades::Projetil*>* LPs);

	};

}


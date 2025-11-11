#pragma once
#include "Obstaculo.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"

namespace Gerenciadores {

	class Gerenciador_Colisoes
	{
		private:
			std::vector<Entidades::Personagens::Inimigo*> LIs;
			std::list<Entidades::Obstaculos::Obstaculo*> LOs;
			std::set< Entidades::Projetil*> LPs;
			Entidades::Personagens::Jogador* pJog1;
			sf::RectangleShape* chao;
		
			// Funções privadas de verificação de colisão
			static Gerenciador_Colisoes* pColisoes;
			Gerenciador_Colisoes(sf::RectangleShape* piso);

			const bool verificaColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
			const bool verificaColisao(sf::RectangleShape* r1, sf::RectangleShape* r2) const;
			const bool verificaColisaoChao(Entidades::Entidade* pe) const;
			void tratarColisoesJogsInimgs();
			void tratarColisoesJogsObstacs();
			void tratarColisoesJogsProjeteis();
			void tratarColisoesJogsChao();
			void tratarColisoesInimigosChao();
			void tratarColisoesInimigosObstacs();
			void tratarColisoesObstacsChao();

		public:
			~Gerenciador_Colisoes();
			Gerenciador_Colisoes* getGerenciadorColisoes();
			void executar();
			void incluirInimigo(Entidades::Personagens::Inimigo* pi);
			void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
			void incluirProjetil(Entidades::Projetil* pj);
			void setJogador(Entidades::Personagens::Jogador* pJog);
			void reposicionar(sf::RectangleShape* c1, sf::RectangleShape* c2);
			void setChao(sf::RectangleShape* piso);
	};

}


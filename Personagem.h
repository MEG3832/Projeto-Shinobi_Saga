#pragma once

#include "Animacao.h"
#include "Entidade.h"

namespace Entidades {

	namespace Personagens {

		class Personagem :public Entidade
		{

		protected:

			int num_vidas;
			float dano;
			bool paraEsq;
			float dt;
			sf::Clock timer;

			//sf::Vector2f veloc;
			//...

		public:

			Personagem(); //passar numero de vidas aqui na construtora (?)
			~Personagem();
			//void salvarDataBuffer();
			virtual void executar() = 0;
			virtual void salvar() = 0;
			virtual void mover() = 0;
			virtual void inicializaAnimacoes() = 0;
			void diminuiVida(float dano);	// Fazer virtual
			int getVida();
			virtual void morrer() = 0;	// Essas 3 funções são virtuais puras pois todos os personagens se ferem e morrem
			virtual bool getFerido() = 0;
			virtual bool getMorto() = 0;
			virtual void setNoChao();

			//virtual int getNumVidas();
			virtual int getDano();
		};

	}
}
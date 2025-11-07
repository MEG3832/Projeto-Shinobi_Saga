#pragma once

#include "Animacao.h"
#include "Entidade.h"

namespace Entidades {

	namespace Personagens {

		class Personagem :public Entidade
		{

		protected:

			int id;
			int num_vidas;
			float dano;
			bool morrendo;
			bool paraEsq;
			bool ferido;
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
			int getVida();
			bool getFerido();

			//virtual int getNumVidas();
			//virtual float getDano();
		};

	}
}
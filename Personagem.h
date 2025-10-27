#pragma once

#include "Header.h"
#include "Animacao.h"
#include "Entidade.h"

namespace Entidades {

	namespace Personagens {

<<<<<<< HEAD
		class Personagem :public Entidade
		{
=======
	int id;
	int num_vidas;

	Animadores::Animacao* animador;

	float dano;

	//sf::Vector2f veloc;
	//...
>>>>>>> animation

		protected:

<<<<<<< HEAD
			int num_vidas;
			//sf::Vector2f veloc;
			//...

		public:
=======
	Personagem();
	~Personagem();
	//void salvarDataBuffer();
	//virtual void executar() = 0;
	//virtual void salvar() = 0;
	virtual void mover() = 0;

	void inicializaAtributos();
	void inicializaAnimacoes();

	
	//virtual int getNumVidas();
	//virtual float getDano();


>>>>>>> animation

			Personagem();
			~Personagem();
			//void salvarDataBuffer();
			virtual void executar() = 0;
			virtual void salvar() = 0;
			virtual void mover() = 0;
		};

	}

}
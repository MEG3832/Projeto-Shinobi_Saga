#pragma once

#include "Personagem.h"


namespace Entidades {

	namespace Personagens {

		class Jogador;

		class Inimigo : public Personagem
		{
			protected:
				int nivel_maldade;

			public:
				Inimigo();
				~Inimigo();
				void salvarDataBuffer();
				virtual void executar();
				virtual void danificar(Jogador* pJ);
				virtual void salvar();
				virtual void mover();
				virtual void inicializaAnimacoes();
		};

	}

}
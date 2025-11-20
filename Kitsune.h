#pragma once
//#include "Projetil.h"
#include "Inimigo.h"
#include "ListaEntidades.h"

namespace Entidades
{
	class Projetil; //forward declaration!

	namespace Personagens
	{
		
		class Kitsune : public Inimigo
		{
			private:

				float raio_ativacao;
				Projetil* pProjetil;

			public:

				Kitsune(Jogador* pJ1, Jogador* pJ2 = nullptr);
				~Kitsune();

				void mover();
				void salvar();
				//void movimento_atq(); //movimento que a kitsune faz enquanto joga os projéteis (ir pra frente e pra trás) ??
				void danificar(Jogador* pJ); // dano no jogador
				void inicializaAnimacoes();

				//Projetil* criaProjetil(); //cria o projétil. joga na lista de entidades e no set do gerenciador de colisões
				void setProjetil(Projetil* pProj);
				void atiraProjetil(); //analisa o tempo de cooldown e o raio de ativação e daí cria o projétil
				int getNvMaldade(); // o projétil vai usá-lo para calcular o dano causado no jogador
				void aumentaNvMaldade(); //também será usado pelo projétil, para que depois da sua colisão com o jogador, o nv de maldade da kitsune aumente em 1.

				void executar();



		};

	}
}



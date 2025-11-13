#pragma once
#include "Projetil.h"
#include "Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		class Kitsune : public Inimigo
		{
			private:

				float raio_ativacao;
				float tempo_cooldown;
				Projetil* pProjetil;
				sf::Clock relogio;

			public:

				Kitsune(Jogador* pJ);
				~Kitsune();

				void mover();
				//void movimento_atq(); //movimento que a kitsune faz enquanto joga os projéteis (ir pra frente e pra trás) ??
				void danificar(Jogador* pJ); // dano no jogador
				void inicializaAnimacoes();

				void criaProjetil(); //cria o projétil. joga na lista de entidades e no set do gerenciador de colisões
				void atiraProjetil(); //analisa o tempo de cooldown e o raio de ativação e daí cria o projétil

				void executar();



		};

	}
}



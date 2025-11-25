/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

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

				const float raio_ativacao;
				Projetil* pProjetil;


				void atiraProjetil(); //analisa o tempo de cooldown e o raio de ativação e daí cria o projétil
				void inicializaAnimacoes();

			public:

				Kitsune(Jogador* pJ1 = nullptr, Jogador* pJ2 = nullptr);
				~Kitsune();

				void mover();
				void salvar();
				void salvarDataBuffer(nlohmann::json& buffer);
				void carregar(const nlohmann::json& j);
				void danificar(Jogador* pJ); // dano no jogador

				//Projetil* criaProjetil(); //cria o projétil. joga na lista de entidades e no set do gerenciador de colisões
				void setProjetil(Projetil* pProj);
				int getNvMaldade(); // o projétil vai usá-lo para calcular o dano causado no jogador
				void aumentaNvMaldade(); //também será usado pelo projétil, para que depois da sua colisão com o jogador, o nv de maldade da kitsune aumente em 1.

				void executar();



		};

	}
}



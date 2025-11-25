/* Inspirado na referência: SIMÃO, J. M. Site das Disciplina de Fundamentos de Programação 2, Curitiba – PR, Brasil
https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++/Fundamentos1-2-LinguagemC++.htm */

#pragma once

#include "Animacao.h"
#include "Entidade.h"

namespace Entidades {

	namespace Personagens {

		class Personagem :public Entidade
		{

		protected:

			// Variaveis
			int num_vidas;
			float dano;
			bool paraEsq;


		public:

			Personagem(); //passar numero de vidas aqui na construtora (?)
			virtual ~Personagem();

			void diminuiVida(float dano);	// Fazer virtual
			int getVida();
			virtual void setNoChao();
			int getDano();
			void salvarDataBuffer(nlohmann::json& buffer);
			void carregar(const nlohmann::json& j);

			// Abstratas
			virtual void executar() = 0;
			virtual void salvar() = 0;
			virtual void mover() = 0;
			virtual void morrer() = 0;	// Essas 3 funções são virtuais puras pois todos os personagens se ferem e morrem
			virtual bool getFerido() = 0;
			virtual bool getMorto() = 0;
			
		};

	}
}
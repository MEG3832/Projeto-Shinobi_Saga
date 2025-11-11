#pragma once

#include "Personagem.h"


namespace Entidades {

	namespace Personagens {

		class Jogador;

		class Inimigo : public Personagem
		{
			protected:
				int nivel_maldade;
				Jogador* jogAlvo;
				bool paraEsq;

				//tratam da ação de atacar: (Tengu e Kitsune usam)

				float cooldownAtaque;
				sf::Clock relogioAtaque; //mede o cooldown

				//tratam da ação de andar:

				bool andando;
				sf::Clock relogioAndar;
				float tempoAndar;

				//tratam do estado ao inimigo ser atacado.
				bool atordoado;
				sf::Clock relogioAtordoado; //mede o cooldown
				float cooldownAtordoado; //p/ duração da animação "Ferido"

				bool estaMorto;
				
				//--//

				void perambular();


			public:

				//construtora e destrutora
				Inimigo(Jogador* pJ);
				virtual ~Inimigo(); //destrutora virtual **
				
				//------//

				virtual void executar() = 0;
				void salvarDataBuffer();
				virtual void salvar();

				//classes filhas (inimigos específicos) vão reimplementar:

				virtual void danificar(Jogador* pJ) = 0;
				virtual void mover() = 0;
				virtual void inicializaAnimacoes() = 0;

				// método com implementação base, mas que pode ser sobrescrito
				virtual void empurrar(Jogador* pJ);

				// getters de estado
				const bool getAtordoado() const { return atordoado; }
				const bool getEstaMorto() const { return estaMorto; }

				virtual bool getIntransponivel() const { return intransponivel; }
				virtual void setIntransponivel(bool val) { intransponivel = val; }
				void setNoChao();
				virtual void diminuiVida(int dano); //para diminuir a vida do inimigo!

		};

	}

}
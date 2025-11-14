#pragma once
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Jogador.h"
#include "Tengu.h"
#include "Plataforma.h"
#include "Fundo.h"
#include "Ente.h"

namespace Fases {

	class Fase:public Ente
	{
	private:
		int maxTengus;
		int maxPlataf;
		
	protected:
		int fim_mapa;	// Teste de tamanho

	protected:

		Listas::ListaEntidades lista_ents;
		Gerenciadores::Gerenciador_Colisoes* GC; //n está exatamente de acordo com o diagrama, mas é para seguir o modelo do singleton
		Entidades::Personagens::Jogador* pJog;

		Parallax::Fundo* pFundo;

		//serão reimplementados da FasePrimeira e na FaseSegunda
		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;
		virtual void criarCenario() = 0;


	public:

		Fase(); //->cria os inimigos, obstáculos dinamicamente e põe da lista de entidades...
		~Fase();

		virtual void executar(); // ->percorre a lista de entidades...
		void criarTengus(); //inimigos em comum nas duas fases.
		void criarPlataformas(); //obstáculo em comum nas duas fases.

		Entidades::Personagens::Jogador* getJogador() { return pJog; }

	/*protected:

		//virtual void criarInimigos() = 0 ;
		//virtual void criarObstaculos() = 0;

		void criarCenario();
		//void criarSamurais();
		//void criarKitsunes();
		
	*/

	};

}




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

		float altura_chao;
		int fim_mapa;	// Teste de tamanho

		Listas::ListaEntidades lista_ents;
		Gerenciadores::Gerenciador_Colisoes* GC; //n está exatamente de acordo com o diagrama, mas é para seguir o modelo do singleton
		Entidades::Personagens::Jogador* pJog1;
		Entidades::Personagens::Jogador* pJog2;
		Parallax::Fundo* pFundo;

	protected :

		// Reimplementacoes
		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;
		virtual void criarCenario() = 0;


	public:

		Fase(Entidades::Personagens::Jogador* pJog1); //->cria os inimigos, obstáculos dinamicamente e põe da lista de entidades...
		Fase(Entidades::Personagens::Jogador* pJog1,Entidades::Personagens::Jogador* pJog2);
		~Fase();

		virtual void executar(); // ->percorre a lista de entidades...
		void criarTengus(); //inimigos em comum nas duas fases.
		void criarPlataformas(); //obstáculo em comum nas duas fases.
		//Entidades::Personagens::Jogador* getJogador();

	};

}




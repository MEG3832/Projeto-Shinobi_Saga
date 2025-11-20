#pragma once
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Gerenciador_de_Eventos.h"
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

		nlohmann::json buffer_fase;

		Listas::ListaEntidades lista_ents;
		Gerenciadores::Gerenciador_Colisoes* GC; //n está exatamente de acordo com o diagrama, mas é para seguir o modelo do singleton
		Gerenciadores::Gerenciador_de_Eventos* GE; 
		Entidades::Personagens::Jogador* pJog;
		Parallax::Fundo* pFundo;

	protected :

		// Reimplementacoes
		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;
		virtual void criarCenario() = 0;
		virtual void salvar() = 0;


	public:

		Fase(); //->cria os inimigos, obstáculos dinamicamente e põe da lista de entidades...
		~Fase();

		virtual void executar(); // ->percorre a lista de entidades...
		void criarTengus(); //inimigos em comum nas duas fases.
		void criarPlataformas(int id); //obstáculo em comum nas duas fases.
		void carregar(const nlohmann::json& j, int id);
		void carregarTengus(const nlohmann::json& j);
		void carregarPlataf(const nlohmann::json& j, int id);
		void carregarJogadores(const nlohmann::json& j);
		Entidades::Personagens::Jogador* getJogador();

	/*protected:

		//virtual void criarInimigos() = 0 ;
		//virtual void criarObstaculos() = 0;

		void criarCenario();
		//void criarSamurais();
		//void criarKitsunes();
		
	*/

	};

}




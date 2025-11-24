#pragma once
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Gerenciador_de_Eventos.h"
#include "Jogador.h"
#include "Tengu.h"
#include "Plataforma.h"
#include "Fundo.h"
#include "Ente.h"
#include "Menu_Salvamento_Ranking.h"

namespace Fases {

	class Fase:public Ente
	{
	private:

		const int maxTengus;
		const int maxPlataf;

		void inicializarTexto();
		void desenharTexto();
		void carregarTengus(const nlohmann::json& j);
		void carregarPlataf(const nlohmann::json& j, const int id);
		void carregarJogadores(const nlohmann::json& j);


	protected:

		int altura_chao;
		int fim_mapa;	// Teste de tamanho

		nlohmann::json buffer_fase;

		Listas::ListaEntidades lista_ents;
		Entidades::Personagens::Jogador* pJog1;
		Entidades::Personagens::Jogador* pJog2;

		Gerenciadores::Gerenciador_Colisoes* GC; //n está exatamente de acordo com o diagrama, mas é para seguir o modelo do singleton
		Gerenciadores::Gerenciador_de_Eventos* GE; 

		Parallax::Fundo* pFundo;

		Menu_Salvamento_Ranking menu_save_rank;

		std::vector<sf::Text> texto_Jog1;
		std::vector<sf::Text> texto_Jog2;
		sf::Font fonte;


		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;
		virtual void criarCenario() = 0;
		void criarTengus(); //inimigos em comum nas duas fases.
		void criarPlataformas(const int id); //obstáculo em comum nas duas fases.
		void carregar(const nlohmann::json& j, const int id);


	public:

		Fase(Entidades::Personagens::Jogador* pJog1 = nullptr); //->cria os inimigos, obstáculos dinamicamente e põe da lista de entidades...
		Fase(Entidades::Personagens::Jogador* pJog1,Entidades::Personagens::Jogador* pJog2);
		~Fase();

		virtual void executar(); // ->percorre a lista de entidades...
		virtual void salvar() = 0;

	};

}




#pragma once

#include "Gerenciador_Grafico.h"
#include "Gerenciador_de_Eventos.h"
<<<<<<< HEAD
#include "Fase.h"
#include "FasePrimeira.h"
#include "Ente.h"
=======
#include "Gerenciador_Colisoes.h"
#include "Plataforma.h"
#include "Redemoinho.h"
#include "Armadilha_de_urso.h"
#include "Kitsune.h"
#include "Samurai_Inimigo.h"
>>>>>>> chefao
#include "Menu.h"


class Jogo {
	private:

		enum Estado {
			MENU_PRINCIPAL,
			MENU_PAUSA,
			FASE1,
			FASE2
		};

		Menu menu;
<<<<<<< HEAD
		Gerenciadores::Gerenciador_Grafico* pGG;
		Gerenciadores::Gerenciador_de_Eventos* pGE;
		Fases::FasePrimeira* pFase1; //o jogador é criado na fase!

		// Variaveis
		Estado estado_atual;
	
=======
		Gerenciadores::Gerenciador_Grafico* GG;	// Singelton
		Parallax::Fundo fundo;
		Entidades::Personagens::Jogador pJog1;
		Gerenciadores::Gerenciador_de_Eventos* GE;	// Singleton
		Entidades::Obstaculos::Plataforma plataforma;
		Entidades::Obstaculos::Redemoinho redemoinho;
		Entidades::Obstaculos::Armadilha_de_urso armadilha_de_urso;
		Entidades::Personagens::Kitsune inimigo;
		Entidades::Projetil projetil;
		Gerenciadores::Gerenciador_Colisoes* GC;	// Um para jogador, que tal?
		Listas::ListaEntidades lista_ents;
		int fase;
>>>>>>> chefao

	public:
		Jogo();
		~Jogo();
		void criarFase();
		void executar();
		void setFase(int num);
};

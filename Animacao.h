#pragma once
#include "Header.h"
#include "Imagem.h"

namespace Animadores {

	class Animacao
	{
		private:

			std::map<std::string, Imagem*> mapImagens; //mapa de texturas... relaciona estado (idle, walk, run...) com Imagem
			sf::Clock clock;
			sf::RectangleShape* corpo; //**
			float dt;

			// Variaveis
			std::string estadoAtual; //guarda qual estado o personagem está: parado, andando, correndo, etc...

		public:

			Animacao(sf::RectangleShape* body = nullptr);
			~Animacao();

			void atualizarAnim(const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg);
			void atualizarAnimProjetil(const bool indoParaEsq, std::string estadoUnico);
			void addAnimacao(const char* caminhoTextura, std::string nomeAnimacao, const int qtdImg, const float frame_duration, const sf::Vector2f scale);

			// Usado no save e no carregamento
			const int getImgAtual();
			const float getTempoTotal();
			const std::string getEstadoAtual();
			void setImgAtual(const int ia);
			void setTempoTotal(const float tt);
			void setEstadoAtual(const std::string ea);

	};

}
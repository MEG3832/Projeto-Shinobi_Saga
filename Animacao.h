#pragma once
#include "Header.h"
#include "Imagem.h"

namespace Animadores {

	class Animacao
	{
		private:

			std::map<std::string, Imagem*> mapImagens; //mapa de texturas... relaciona estado (idle, walk, run...) com Imagem

			// Variaveis
			sf::RectangleShape* corpo; //**
			sf::Clock clock;
			std::string estadoAtual; //guarda qual estado o personagem está: parado, andando, correndo, etc...

		public:

			Animacao(sf::RectangleShape* body);
			~Animacao();

			void atualizarAnimJog(const bool caindo, const bool subindo, const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg);
			void atualizarAnimInim(const bool indoParaEsq, const bool rodaUmaVez, std::string estadoImg);
			//void atualizarAnimProjetil(const bool indoParaEsq, std::string estadoUnico);
			void addAnimacao(const char* caminhoTextura, std::string nomeAnimacao, const int qtdImg, const float frame_duration, const sf::Vector2f scale);
			const int getImgAtual(std::string nomeAnimacao);

	};

}
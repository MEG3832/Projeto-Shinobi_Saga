#pragma once
#include "Ente.h"

namespace Parallax {

	class Fundo : public Ente
	{
		private:

			class Camada
			{
				private:
					const sf::Vector2f tamJanela;
					sf::IntRect dimensao;
					const float vel;

					sf::Texture textura;
					sf::RectangleShape fundo;
					sf::RectangleShape fundoAuxiliar;

					void trocarTextura();

				public:
					Camada(sf::Vector2f tamJanela, sf::Texture textura, const float vel);
					~Camada();
					void desenharCamada(sf::RenderWindow* window);	// GG desenha!
					void atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual);
			};

			sf::Vector2f posAnteriorCamera;
			std::vector<Camada*> camadas;

		public:
			Fundo();
			~Fundo();
			void executar();	// Atualiza a posição de cada uma das camadas se houver velocidade e desenha elas
			void desenhar();
			void addCamada(const char* caminhoTextura, const float vel);
	};

}
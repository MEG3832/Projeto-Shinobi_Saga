#pragma once
#include "Entidade.h"
namespace Parallax {

	class Fundo : public Ente
	{
		private:

			class Camada
			{
				private:
					const sf::Vector2f tam;
					sf::IntRect dimensao;
					const float vel;

					sf::Texture textura;
					sf::RectangleShape fundo;
					sf::RectangleShape fundoAuxiliar;

					void trocarTextura();

				public:
					Camada(sf::Vector2f tam, sf::Texture text, const float vel);
					Camada();
					~Camada();
					void desenharCamada(sf::RenderWindow* window);
					void atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual);
			};

			sf::Vector2f posAnteriorCamera;
			std::vector<Camada*> camadas;

			void desenhar();


		public:
			Fundo();
			~Fundo();
			void executar();	// Atualiza a posição de cada uma das camadas se houver velocidade e desenha elas
			void addCamada(const sf::Vector2f tam, const float vel, const char* caminhoTextura = nullptr);
	};

}
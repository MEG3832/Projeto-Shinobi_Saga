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
					Camada(sf::Vector2f tam, sf::Texture textura, const float vel);
					Camada(sf::Vector2f tam, float vel);	// Para o chão
					~Camada();
					void desenharCamada(sf::RenderWindow* window);
					void atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual);
					sf::RectangleShape* getChao();
			};

			sf::Vector2f posAnteriorCamera;
			std::vector<Camada*> camadas;

		public:
			Fundo();
			~Fundo();
			void executar();	// Atualiza a posição de cada uma das camadas se houver velocidade e desenha elas
			void desenhar();
			void addCamada(const float vel = 0.0f, const char* caminhoTextura = nullptr);
			sf::RectangleShape* getChao();
	};

}
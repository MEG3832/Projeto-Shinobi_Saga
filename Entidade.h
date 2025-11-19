#pragma once

#include "Animacao.h"
#include "Ente.h"

namespace Entidades {

	class Entidade :public Ente
	{
	protected:

			static nlohmann::json buffer_plataformas;
			static nlohmann::json buffer_redemoinhos;
			static nlohmann::json buffer_tengus;
			static nlohmann::json buffer_samurais;
			static nlohmann::json buffer_jogadores;

			sf::Vector2f pos;	// Nao estou usando, pois corpo->getPosition() eh equivalente

			// Variavies
			sf::Vector2f veloc;
			Animadores::Animacao* animador;
			bool intransponivel;

			void carregar(const nlohmann::json& j);
			void salvarDataBuffer(nlohmann::json& buffer);

		public:

			Entidade();
			virtual ~Entidade();

			void setAnimador(sf::RectangleShape* body);
			bool getIntransponivel();
			void setIntransponivel(bool intangivel);
			void sofrerGravidade();
			sf::Vector2f getPos(); // Nao usei, posso tirar? corpo->getPosition() eh equivalente

			static nlohmann::json getArrayPlataformas();
			static nlohmann::json getArrayRedemoinhos();
			static nlohmann::json getArrayTengus();
			static nlohmann::json getArraySamurais();
			static nlohmann::json getArrayJogadores();
			static void limparBuffers();

			// Abstratas
			virtual void executar() = 0;
			virtual void salvar() = 0;


	};

}
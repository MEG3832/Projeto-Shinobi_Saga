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
			static nlohmann::json buffer_armadilhas;
			static nlohmann::json buffer_kitsunes;
			static nlohmann::json buffer_projeteis;
			static nlohmann::json buffer_jogadores;

			// Variavies
			sf::Vector2f veloc;
			Animadores::Animacao* animador;
			bool intransponivel;

			void carregar(const nlohmann::json& j);

		public:

			Entidade();
			virtual ~Entidade();

			void setAnimador(sf::RectangleShape* body);
			bool getIntransponivel();
			void setIntransponivel(const bool intangivel);
			void sofrerGravidade();
			void salvarDataBuffer(nlohmann::json& buffer);

			static nlohmann::json getArrayPlataformas();
			static nlohmann::json getArrayRedemoinhos();
			static nlohmann::json getArrayTengus();
			static nlohmann::json getArraySamurais();
			static nlohmann::json getArrayArmadilhas();
			static nlohmann::json getArrayKitsunes();
			static nlohmann::json getArrayProjeteis();
			static nlohmann::json getArrayJogadores();
			static void limparBuffers();

			// Abstratas
			virtual void executar() = 0;
			virtual void salvar() = 0;


	};

}
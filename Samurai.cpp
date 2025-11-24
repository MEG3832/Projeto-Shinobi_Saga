#include "Samurai.h"
#include "Jogador.h"

namespace Entidades {
	namespace Personagens {

		Samurai::Samurai(Jogador* pJ1, Jogador* pJ2, float resist) :
			Inimigo(pJ1, pJ2),
			cooldownEmpurrao(4.0f),
			timer(),
			dt(0.0),
			resistencia(resist),
			empurra(true)
		{
			timer.restart();
			nivel_maldade = 1; // nível de maldade base
			paraEsq = true;
			veloc = sf::Vector2f(0.5f, 0.0f);
			tempoAndar = 0.5f;
			num_vidas = 75;
			cooldownAtordoado = 1.0f;

			corpo = new sf::RectangleShape(sf::Vector2f(200.0f, 200.0f));
			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 145, corpo->getSize().y));

			inicializaAnimacoes();
		}

		Samurai::~Samurai() {
			timer.restart();
			resistencia = 0.0;
			empurra = false;
			dt = 0.0;
		}

		void Samurai::executar()
		{
			Inimigo::executar(); //será que posso só fazer isso?
		}

		void Samurai::mover()
		{
			perambular(); //ele só perambula!
		}

		void Samurai::salvar() {
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_samurais.push_back(buffer);
		}

		void Samurai::salvarDataBuffer(nlohmann::json& buffer) {
			Inimigo::salvarDataBuffer(buffer);

			buffer["dt"] = dt;
			buffer["resistencia"] = resistencia;
			buffer["empurra"] = empurra;
		}

		void Samurai::carregar(const nlohmann::json& j) {
			try {
				dt = j.at("dt").get<float>();
				resistencia = j.at("resistencia").get<float>();
				empurra = j.at("empurra").get<bool>();
			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Alguma das chaves estah ausente." << e.what() << std::endl;
			}

			Inimigo::carregar(j);
		}

		void Samurai::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				int dano_calculado = nivel_maldade * 10; //dano base
				nivel_maldade++; //aumentamos o nivel de maldade no mometo em que o jogador e o samurai entram em contato

				if (empurra) {
					pJ->diminuiVida(dano_calculado);
					empurrar(pJ);
					empurra = false;	// Comeca o cooldown do empurrao
					dt = 0.0;
					timer.restart();
				}

				dt += timer.getElapsedTime().asSeconds();
				timer.restart();

				if (!empurra && dt >= cooldownEmpurrao) {
					empurra = true;
					dt = 0.0;
					timer.restart();
				}
			}
			else
			{
				std::cerr << "ERRO: Nao eh possivel danificar o jogador pois o ponteiro para ele eh NULL" << std::endl;
			}
		}

		void Samurai::diminuiVida(float dano)
		{
			if (FERIDO == estado_atual || MORRENDO == estado_atual) {
				return;
			}

			float dano_reduzido = 0.0f;
			if (resistencia > 0.0f) {
				dano_reduzido = dano / resistencia;
			}
			else {
				dano_reduzido = dano; //para evitar divisão por zero
			}

			Inimigo::diminuiVida(dano_reduzido);
		}

		void Samurai::inicializaAnimacoes()
		{
			if (corpo) {
				setAnimador(corpo);
			}

			else {
				std::cerr << "ERRO: nao eh possivel inicializar o animador pois o corpo eh NULL" << std::endl;
			}


			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Samurai/Idle.png", "Parado", 5, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai/Walk.png", "Andando", 9, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.0, 1.0));


				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Samurai/Attack_1.png", "Ataque1", 4, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai/Attack_2.png", "Ataque2", 5, 0.12f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai/Attack_3.png", "Ataque3", 4, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai/Hurt.png", "Ferido", 2, 0.17f, sf::Vector2f(1.0, 1.0));

			}
			else
				std::cerr << "ponteiro de animacao nulo!" << std::endl;
		}

	}
}
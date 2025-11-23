#include "Samurai_Inimigo.h"
#include "Jogador.h"

namespace Entidades {
	namespace Personagens {

		Samurai_Inimigo::Samurai_Inimigo(Jogador* pJ1, Jogador* pJ2, float resist) :
			Inimigo(pJ1, pJ2),
			cooldownEmpurrao(4.0f),
			timer(),
			resistencia(resist),
			empurra(true),
			dt(0.0)
		{
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

		Samurai_Inimigo::~Samurai_Inimigo() {
			cooldownEmpurrao = 0.0;
			timer.restart();
			resistencia = 0.0;
			empurra = false;
			dt = 0.0;
		}

		void Samurai_Inimigo::executar()
		{
			Inimigo::executar(); //será que posso só fazer isso?
		}

		void Samurai_Inimigo::mover()
		{
			perambular(); //ele só perambula!
		}

		void Samurai_Inimigo::salvar() {
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_samurais.push_back(buffer);
		}

		void Samurai_Inimigo::salvarDataBuffer(nlohmann::json& buffer) {
			Inimigo::salvarDataBuffer(buffer);

			buffer["dt"] = dt;
			buffer["resistencia"] = resistencia;
			buffer["empurra"] = empurra;
		}

		void Samurai_Inimigo::carregar(const nlohmann::json& j) {
			dt = j.at("dt").get<float>();
			resistencia = j.at("resistencia").get<float>();
			empurra = j.at("empurra").get<bool>();

			Inimigo::carregar(j);
		}

		void Samurai_Inimigo::danificar(Jogador* pJ)
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
				std::cout << "ERRO: Nao eh possivel danificar o jogador pois o ponteiro para ele eh NULL" << std::endl;
			}
		}

		void Samurai_Inimigo::diminuiVida(float dano)
		{
			if (FERIDO == estado_atual || MORRENDO == estado_atual) {
				return;
			}

			int dano_reduzido = 0;
			if (resistencia > 0.0f) {
				dano_reduzido = dano / resistencia;
			}
			else {
				dano_reduzido = dano; //para evitar divisão por zero
			}

			Inimigo::diminuiVida(dano_reduzido);
		}

		void Samurai_Inimigo::inicializaAnimacoes()
		{
			if (corpo) {
				setAnimador(corpo);
			}

			else {
				std::cerr << "ERRO: nao eh possivel inicializar o animador pois o corpo eh NULL" << std::endl;
			}


			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Samurai_Inimigo/Idle.png", "Parado", 5, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Walk.png", "Andando", 9, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.0, 1.0));


				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Samurai_Inimigo/Attack_1.png", "Ataque1", 4, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Attack_2.png", "Ataque2", 5, 0.12f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Attack_3.png", "Ataque3", 4, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Samurai_Inimigo/Hurt.png", "Ferido", 2, 0.17f, sf::Vector2f(1.0, 1.0));

			}
			else
				std::cout << "ponteiro de animacao nulo!" << std::endl;
		}

	}
}
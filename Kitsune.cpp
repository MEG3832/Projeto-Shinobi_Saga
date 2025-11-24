#include "Kitsune.h"
#include "Projetil.h"

namespace Entidades
{
	namespace Personagens
	{
		Kitsune::Kitsune(Jogador* pJ1, Jogador* pJ2) :
			Inimigo(pJ1, pJ2),
			raio_ativacao(250),
			pProjetil(nullptr)
		{
			cooldownAtaque = 3.0f;
			nivel_maldade = 1; // nível de maldade base
			paraEsq = true;
			veloc = sf::Vector2f(0.5f, 0.0f);
			tempoAndar = 4.0f;

			num_vidas = 200;

			cooldownAtordoado = 1.0f;

			corpo = new sf::RectangleShape(sf::Vector2f(170.0f, 150.0f));
			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 120.0f, corpo->getSize().y));

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Kitsune::~Kitsune()
		{
			pProjetil = nullptr;
		}


		void Kitsune::executar()
		{
			atualizarAlvo();

			if (jogAlvo && !jogAlvo->getMorto())
				Inimigo::executar(); //verificar se basta isso...

			if (MORRENDO == estado_atual && animador->getImgAtual() == 9) {
				if (corpo) {
					corpo->setFillColor(sf::Color::Transparent);
				}

				else {
					std::cerr << "ERRO: Nao eh possivel deixar a kitsune transparente pois seu corpo eh NULL" << std::endl;
				}
			}

		}


		void Kitsune::mover()
		{
			if (corpo) {

				if (animador) {

					if (jogAlvo) {

						if (jogAlvo->getCorpo()) {

							//posição em x
							float posJog_X = jogAlvo->getCorpo()->getPosition().x + jogAlvo->getCorpo()->getSize().x / 2;
							float posInim_X = corpo->getPosition().x + corpo->getSize().x / 2;

							float distHorizontal = abs(posJog_X - posInim_X);

							//posição em y

							float posJog_Y = jogAlvo->getCorpo()->getPosition().y + jogAlvo->getCorpo()->getSize().y / 2;
							float posInim_Y = corpo->getPosition().y + corpo->getSize().y / 2;

							float distVertical = abs(posJog_Y - posInim_Y);

							float raio_vertical = corpo->getSize().y / 2;

							if (distHorizontal <= raio_ativacao && distVertical <= raio_vertical)
							{
								//verifica em que lado o jogador está...

								if (posJog_X < posInim_X) //jogador está à esquerda do inimigo
								{
									paraEsq = true;

								}

								else //jogador está à direita do inimigo
								{
									paraEsq = false;

								}

								if (pProjetil && relogioAtaque.getElapsedTime().asSeconds() >= cooldownAtaque && !pProjetil->getEstadoProj())
								{
									animador->atualizarAnim(paraEsq, true, "Ataque3"); //se o cooldown está pronto, primeiro tocamos a animação!

									if (animador->getImgAtual() == 6) //se chegou no último frame, pode atacar!
									{
										atiraProjetil();
									}
								}
								else
								{
									animador->atualizarAnim(paraEsq, false, "Parado");
								}

							}

							else
								perambular();
						}

						else {
							std::cerr << "ERRO: Nao eh possivel mover a kitsune pois o corpo do jogador eh NULL" << std::endl;
						}
					}

					else {
						std::cerr << "ponteiro do jogador eh nulo!" << std::endl;
					}
				}

				else {
					std::cerr << "ERRO: nao eh posivel mover a kitsune pois seu animador eh NULL" << std::endl;
				}
			}

			else {
				std::cerr << "ERRO: Nao eh possivel mover a kitsune pois seu corpo eh NULL" << std::endl;
			}
		}

		void Kitsune::atiraProjetil()
		{
			if (pProjetil) {
				if (pProjetil->getCorpo()) {
					relogioAtaque.restart();

					pProjetil->setEstadoProj(true); //apenas setamos o estado do projétil, já que o que será feito (dependendo do estado dele), será tratado no executar do projétil.

					if (paraEsq) {
						pProjetil->getCorpo()->setPosition(corpo->getPosition().x, corpo->getPosition().y + 25.0f); //centralizo o projétil bem na frente da kitsune
						pProjetil->setVelocidade(sf::Vector2f(-3.0f, 0.0f));
					}
					else {

						pProjetil->getCorpo()->setPosition(corpo->getPosition().x + corpo->getSize().x / 2, corpo->getPosition().y + 25.0f);
						pProjetil->setVelocidade(sf::Vector2f(3.0f, 0.0f));
					}
				}
			}

		}

		void Kitsune::salvar()
		{
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_kitsunes.push_back(buffer);
		}

		void Kitsune::salvarDataBuffer(nlohmann::json& buffer) {

			Inimigo::salvarDataBuffer(buffer);
		}

		void Kitsune::carregar(const nlohmann::json& j) {

			Inimigo::carregar(j);
		}

		void Kitsune::setProjetil(Projetil* pProj)
		{
			if (pProj)
				pProjetil = pProj;
			else
				std::cerr << "ponteiro do projetil eh nulo!" << std::endl;
		}

		void Kitsune::inicializaAnimacoes()
		{
			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Kitsune/Idle.png", "Parado", 8, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Walk.png", "Andando", 8, 0.20f, sf::Vector2f(1.0, 1.0));


				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Kitsune/Attack_3.png", "Ataque3", 7, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Dead.png", "Derrotado", 10, 0.15f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Kitsune/Hurt.png", "Ferido", 2, 0.17f, sf::Vector2f(1.0, 1.0));

			}
			else
				std::cerr << "ponteiro de animacao nulo!" << std::endl;
		}

		void Kitsune::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				int dano_causado = 200;
				pJ->diminuiVida((float)dano_causado);
				empurrar(pJ); // Chama o empurrão (pode ser o base 'Inimigo::empurrar')
			}
			else
			{
				std::cerr << "ponteiro de jogador nulo!" << std::endl;
			}
		}

		int Kitsune::getNvMaldade()
		{
			return nivel_maldade;
		}

		void Kitsune::aumentaNvMaldade()
		{
			nivel_maldade++;
		}

	}
}
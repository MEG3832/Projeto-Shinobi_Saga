#include "Tengu.h"
#include "Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Tengu::Tengu(Jogador* pJ1, Jogador* pJ2) :
			Inimigo(pJ1,pJ2),
			raio_perseg(250.0f)
		{
			paraEsq = true;
			nivel_maldade = 1;
			veloc = sf::Vector2f(0.5, 0.0);
			num_vidas = 100;

			cooldownAtordoado = 2.0f;
			tempoAndar = 2.5f; // Tempo de "perambular" específico

			corpo = new sf::RectangleShape(sf::Vector2f(180.0f, 160.0f));
			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 80.0, corpo->getSize().y));

			inicializaAnimacoes();
		}

		Tengu::~Tengu()
		{
			raio_perseg = 0.0;
		}

		void Tengu::diminuiVida(int dano)
		{
			if (FERIDO == estado_atual || MORRENDO == estado_atual) {
				return;
			}

			Inimigo::diminuiVida(dano); // Chama a base para perder vida

			if (!(MORRENDO == estado_atual)) {
				nivel_maldade++; // Aumenta o nível de maldade
				std::cout << "Tengu enfurecido! Nivel de maldade: " << nivel_maldade << std::endl;
			}

		}

		void Tengu::danificar(Jogador* pJ)
		{
			if (pJ)
			{
				int dano_calculado = nivel_maldade * 50; // Dano = nivel_maldade * 50
				pJ->diminuiVida(dano_calculado);
				std::cout << "Tengu causou " << dano_calculado << " de dano! Vida do Jogador: " << pJ->getVida() << std::endl;
				empurrar(pJ); // Chama o empurrão (pode ser o base 'Inimigo::empurrar')
			}
			else
			{
				std::cout << "ponteiro de jogador nulo!" << std::endl;
			}
		}

		void Tengu::executar()
		{
			atualizarAlvo();

			if (jogAlvo && !jogAlvo->getMorto()) {
				Inimigo::executar();
			}
		}

		void Tengu::perseguir(Jogador* pJ)
		{
			if (pJ) {

				if (pJ->getHitBox()) {

					if (corpo) {

						if (hitBox) {

							float posJog_X = pJ->getHitBox()->getPosition().x + pJ->getHitBox()->getSize().x / 2;
							float posInim_X = hitBox->getPosition().x + hitBox->getSize().x / 2;


							float distanciaCentros = abs(posJog_X - posInim_X);
							float distanciaAtaque = abs((pJ->getHitBox()->getSize().x / 2) + hitBox->getSize().x / 2) + 39.0f; //ajuste da distancia por testes

							if (distanciaCentros <= raio_perseg && distanciaCentros > distanciaAtaque)
							{
								if (posJog_X < posInim_X) //jogador está à esquerda do inimigo
								{
									paraEsq = true;
									animador->atualizarAnimInim(paraEsq, false, "Correndo");
									corpo->move(-veloc.x, 0.0f);
									hitBox->move(-veloc.x, 0.0f);

								}

								else if (posJog_X > posInim_X) //jogador está à direita do inimigo
								{
									paraEsq = false;
									animador->atualizarAnimInim(paraEsq, false, "Correndo");
									corpo->move(veloc.x, 0.0f);
									hitBox->move(veloc.x, 0.0f);

								}

							}

							else if (distanciaCentros <= distanciaAtaque) //entrou na área de ataque!
							{
								dt_ataque += relogioAtaque.getElapsedTime().asSeconds();
								relogioAtaque.restart();

								if (dt_ataque >= cooldownAtaque)
								{
									animador->atualizarAnimInim(paraEsq, true, "Ataque3"); //se o cooldown está pronto, primeiro tocamos a animação!

									if (animador->getImgAtual() == 2) //se chegou no último frame, pode atacar!
									{
										atacar(pJ);
									}
								}
								else
								{
									animador->atualizarAnimInim(paraEsq, false, "Parado");
								}
							}
						}

						else {
							std::cerr << "ERRO: Nao eh possivel perseguir o jogador pois o hit box do inimigo eh NULL" << std::endl;
						}
					}

					else {
						std::cerr << "ERRO: Nao eh possivel perseguir o jogador pois o corpo do inimigo eh NULL" << std::endl;
					}
				}

				else {
					std::cerr << "ERRO: Nao eh possivel perseguir o jogador pois o hit box dele eh NULL" << std::endl;
				}

			}

			else {
				std::cout << "ERRO: Nao eh possivel perseguir o jogador pois o ponteiro dele eh NULL" << std::endl;
			}
		}

		void Tengu::atacar(Jogador* pJ)
		{

			if (pJ)
			{ 
				if (corpo) {

					if (hitBox) {

						dt_ataque += relogioAtaque.getElapsedTime().asSeconds();
						relogioAtaque.restart();

						if (dt_ataque >= cooldownAtaque)
						{
							dt_ataque = 0.0;
							relogioAtaque.restart();

							if (paraEsq)
							{
								float investida = -40.0f;
								corpo->move(investida, 0.0f);
								hitBox->move(investida, 0.0f);
							}

							else
							{
								float investida = 40.0f;
								corpo->move(investida, 0.0f);
								hitBox->move(investida, 0.0f);
							}

						}
					}

					else {
						std::cerr << "ERRO: Nao eh possivel atacar ojogador pois o hit box do inimigo eh NULL" << std::endl;
					}
				}

				else {
					std::cerr << "ERRO: Nao eh possivel atacar ojogador pois o corpo do inimigo eh NULL" << std::endl;
				}

			}

			else
				std::cout << "ERRO: Nao eh possivel atacar o jogador pois o ponteiro dele eh NULL" << std::endl;
		}


		void Tengu::inicializaAnimacoes()
		{
			setAnimador(corpo);

			if (animador) {

				//Animações em loop

				animador->addAnimacao("Imagens/Tengu/Idle.png", "Parado", 6, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Walk.png", "Andando", 8, 0.20f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(1.0, 1.0));


				//Animações que só devem rodar uma vez

				animador->addAnimacao("Imagens/Tengu/Attack_1.png", "Ataque1", 6, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Attack_2.png", "Ataque2", 4, 0.12f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Attack_3.png", "Ataque3", 3, 0.1f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Dead.png", "Derrotado", 6, 0.3f, sf::Vector2f(1.0, 1.0));
				animador->addAnimacao("Imagens/Tengu/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(1.0, 1.0));
			}

			else
				std::cout << "ERRO: Nao eh possivel inicializar a animacao pois o animador eh NULL" << std::endl;
		}


		void Tengu::mover()
		{
			if (jogAlvo) {

				if (jogAlvo->getCorpo()) {
					 
					if (corpo) {

						if (hitBox) {

							//posição em x
							float posJog_X = jogAlvo->getCorpo()->getPosition().x + jogAlvo->getCorpo()->getSize().x / 2;
							float posInim_X = corpo->getPosition().x + corpo->getSize().x / 2;

							float distHorizontal = abs(posJog_X - posInim_X);

							//posição em y

							float posJog_Y = jogAlvo->getCorpo()->getPosition().y + jogAlvo->getCorpo()->getSize().y / 2;
							float posInim_Y = corpo->getPosition().y + corpo->getSize().y / 2;

							float distVertical = abs(posJog_Y - posInim_Y); // verificamos em y para evitar a perseguição sem sentido se o jogador estiver mto acima ou abaixo do inimigo

							float raio_vertical = corpo->getSize().y / 2; //esse seria o "raio_perseg" na vertical...

							if (distHorizontal <= raio_perseg && distVertical <= raio_vertical)
								perseguir(jogAlvo);

							else
								perambular();
						}

						else {
							std::cout << "ERRO: Nao eh possivel mover o tengu pois o hit box dele eh NULL" << std::endl;
						}
					}

					else {
						std::cout << "ERRO: Nao eh possivel mover o tengu pois o corpo dele eh NULL" << std::endl;
					}
				}

				else {
					std::cout << "ERRO: Nao eh possivel mover o tengu pois o ponteiro do jogador eh NULL" << std::endl;
				}

			}

			else
			{
				std::cout << "ERRO: Nao eh possivel mover o tengu pois o ponteiro para jogador eh NULL" << std::endl;
			}
		}

		void Tengu::salvar() {
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_tengus.push_back(buffer);
		}

		void Tengu::salvarDataBuffer(nlohmann::json& buffer) {

			Inimigo::salvarDataBuffer(buffer);

			buffer["raio_perseg"] = raio_perseg;
		}

		void Tengu::carregar(const nlohmann::json& j) {
			raio_perseg = j.at("raio_perseg").get<float>();

			Inimigo::carregar(j);
		}


	}
}
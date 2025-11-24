#include "Inimigo.h"
#include "Jogador.h"

namespace Entidades {

	namespace Personagens {

		Inimigo::Inimigo(Jogador* pJ1, Jogador* pJ2) :
			Personagem(),
			pJogador1(pJ1),
			pJogador2(pJ2),
			jogAlvo(pJ1), // começa focando no 1 por padrão
			cooldownAtaque(3.0f),
			tempoAndar(3.0),
			cooldownAtordoado(0.5f), // Valor padrão
			nivel_maldade(1),
			relogioAndar(),
			relogioAtaque(),
			relogioAtordoado(),
			estado_atual(PARADO),
			dt_ataque(0.0),
			dt_andar(0.0),
			dt_atordoamento(0.0)
		{
			//corpo é feito nas classes folha
			veloc = sf::Vector2f(0.5, 0.0);
		}

		Inimigo::~Inimigo() {

			nivel_maldade = -1;
			veloc = sf::Vector2f(0.0, 0.0);
			jogAlvo = nullptr;
			cooldownAtaque = 0.0;
			tempoAndar = 0.0;
			cooldownAtordoado = 0.0;
			dt_ataque = 0.0;
			dt_andar = 0.0;
			dt_atordoamento = 0.0;
			relogioAndar.restart();
			relogioAtordoado.restart();
			relogioAtaque.restart();
			estado_atual = PARADO;
		}

		void Inimigo::salvarDataBuffer(nlohmann::json& buffer) {
			Personagem::salvarDataBuffer(buffer);

			buffer["nivel_maldade"] = nivel_maldade;
			buffer["dt_ataque"] = dt_ataque;
			buffer["dt_andar"] = dt_andar;
			buffer["dt_atordoamento"] = dt_atordoamento;
			buffer["estado_atual"] = estado_atual;
		}

		void Inimigo::carregar(const nlohmann::json& j) {
			try {
				nivel_maldade = j.at("nivel_maldade").get<int>();
				dt_ataque = j.at("dt_ataque").get<float>();
				dt_andar = j.at("dt_andar").get<float>();
				dt_atordoamento = j.at("dt_atordoamento").get<float>();
				estado_atual = static_cast<Entidades::Personagens::Inimigo::Estado>(j.at("estado_atual").get<int>());
			}
			catch (const nlohmann::json::out_of_range& e) {
				std::cerr << "ERRO: Alguma das chaves estah ausente." << e.what() << std::endl;
			}

			Personagem::carregar(j);
		}

		void Inimigo::executar() {

			atualizarAlvo();

			if (animador) {

				if (MORRENDO == estado_atual) {
					animador->atualizarAnim(paraEsq, true, "Derrotado");
				}

				else if (FERIDO == estado_atual) {

					dt_atordoamento += relogioAtordoado.getElapsedTime().asSeconds();
					relogioAtordoado.restart();

					if (dt_atordoamento >= cooldownAtordoado) {
						estado_atual = PARADO;
						dt_andar = 0.0;
						relogioAndar.restart();
					}
					else {
						animador->atualizarAnim(paraEsq, true, "Ferido");
					}
				}

				else {
					mover();
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel excutar o inimigo pois o animador eh NULL" << std::endl;
			}
		}

		void Inimigo::atualizarAlvo() {

			float dist1 = 100000.0f; // valor muito alto inicial
			float dist2 = 100000.0f;

			// Calcula distância para Jogador 1 (se existir e estiver vivo)
			if (pJogador1 && !pJogador1->getMorto() && pJogador1->getCorpo()) {
				float dx = pJogador1->getCorpo()->getPosition().x - corpo->getPosition().x;
				float dy = pJogador1->getCorpo()->getPosition().y - corpo->getPosition().y;
				dist1 = std::sqrt(dx * dx + dy * dy);
			}

			// Calcula distância para Jogador 2 (se existir e estiver vivo)
			if (pJogador2 && !pJogador2->getMorto() && pJogador2->getCorpo()) {
				float dx = pJogador2->getCorpo()->getPosition().x - corpo->getPosition().x;
				float dy = pJogador2->getCorpo()->getPosition().y - corpo->getPosition().y;
				dist2 = std::sqrt(dx * dx + dy * dy);
			}

			// decide quem é o alvo
			if (dist1 < dist2) {
				jogAlvo = pJogador1;
			}
			else if (dist2 < dist1) {
				jogAlvo = pJogador2;
			}
			else {
				jogAlvo = nullptr; // ninguém por perto ou ambos mortos
			}
		}

		void Inimigo::diminuiVida(int dano)
		{
			if (corpo) {
				//não toma dano se já estiver atordoado ou morto
				if (FERIDO != estado_atual && MORRENDO != estado_atual) {

					// não faz nada se o dano for 0 ou negativo
					if (dano <= 0) {
						return;
					}

					// Na verdade precisa adaptar para o caso em que quem estah atacando eh o outro jogador e nao o alvo
					if (jogAlvo) {
						if (corpo) {
							if (jogAlvo->getCorpo()->getPosition().x < corpo->getPosition().x) {
								paraEsq = true;
							}
							else
							{
								paraEsq = false;
							}
						}
						else {
							std::cerr << "ERRO: nao eh possivel virar o inimigo pois o corpo dele eh NULL" << std::endl;
						}
					}
					else {
						std::cerr << "ERRO: nao eh possivel virar o inimigo pois o jogador alvo eh NULL" << std::endl;
					}

					Personagem::diminuiVida(dano); // aplica o dano (da classe Personagem)

					// verifica o resultado do ataque
					if (getVida() <= 0) {
						jogAlvo->aumentaPontuacao(20);	// Exemplo
						estado_atual = MORRENDO;
						setIntransponivel(false); // Inimigo morto pode ser atravessado
					}
					else {
						// Se tomou dano mas não morreu, fica atordoado
						estado_atual = FERIDO;
						dt_atordoamento = 0.0;
						relogioAtordoado.restart();
					}
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel diminuir a vida do inimigo pois seu corpo eh NULL" << std::endl;
			}
		}

		void Inimigo::empurrar(Jogador* pJ) //empurrão base
		{
			//nesse método, vamos calcular a direção do vetor KnockBack que queremos passar para o jogador,
			// e, depois disso, iremos multiplicar por uma "força" (intensidade)

			sf::Vector2f velKnockBack;
			float força_empurrao = 8.0f;

			if (pJ) {

				if (corpo) {

					if (pJ->getCorpo()) {
						//calcula os centros do inimigo e do jogador

						sf::Vector2f centroJog = pJ->getCorpo()->getPosition() + (pJ->getTam()) / 2.0f;
						sf::Vector2f centroInim = corpo->getPosition() + (corpo->getSize()) / 2.0f;

						sf::Vector2f vetor = centroJog - centroInim; //nessa ordem!

						//normalizamos o vetor... e para isso, calculamos seu módulo

						float modulo = std::sqrt(vetor.x * vetor.x + vetor.y * vetor.y);

						if (modulo != 0)
							vetor = vetor / modulo; //agora o vetor é um vetor normalizado!

						vetor *= força_empurrao;

						pJ->setVelKnockBack(vetor);
					}

					else {
						std::cerr << "ERRO: NAO eh possivel empurrar o jogador pois o corpo do dele eh NULL" << std::endl;
					}
				}

				else {
					std::cerr << "ERRO: NAO eh possivel empurrar o jogador pois o corpo do inimigo eh NULL" << std::endl;
				}

			}

			else
				std::cerr << "ERRO: NAO eh possivel empurrar o jogador pois ele eh NULL" << std::endl;

		}

		void Inimigo::perambular()
		{
			if (corpo) {

				if (hitBox) {

					if (animador) {

						dt_andar += relogioAndar.getElapsedTime().asSeconds();
						relogioAndar.restart();

						if (dt_andar >= tempoAndar)
						{
							dt_andar = 0.0;
							relogioAndar.restart();

							if (ANDANDO == estado_atual) {
								estado_atual = PARADO;
							}
							else {
								estado_atual = ANDANDO;
							}

							paraEsq = (rand() % 2 == 0);
						}

						if (ANDANDO == estado_atual)
						{
							if (paraEsq) {
								corpo->move(-veloc.x, 0.0f);
								hitBox->move(-veloc.x - 0.5f, 0.0f);
							}
							else {
								corpo->move(veloc.x, 0.0f);
								hitBox->move(veloc.x, 0.0f);
							}

							animador->atualizarAnim(paraEsq, false, "Andando");
						}
						else
						{
							animador->atualizarAnim(paraEsq, false, "Parado");
						}
					}

					else {
						std::cerr << "ERRO: NAO eh possivel perambular pois o animador do inimigo eh NULL" << std::endl;
					}
				}

				else {
					std::cerr << "ERRO: NAO eh possivel perambular pois o hit box do inimigo eh NULL" << std::endl;
				}
			}
			else {
				std::cerr << "ERRO: NAO eh possivel perambular pois o corpo do inimigo eh NULL" << std::endl;
			}
		}

		void Inimigo::setJogAlvo(Jogador* pJog)
		{
			jogAlvo = pJog;
		}

		void Inimigo::morrer() {
			estado_atual = MORRENDO;
		}

		bool Inimigo::getFerido() {
			if (FERIDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

		bool Inimigo::getMorto() {
			if (MORRENDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

	}

}
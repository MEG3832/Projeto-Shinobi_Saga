#include "Jogador.h"
#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		Jogador::Jogador(int ident) :
			Personagem(),
			cooldown_ataque(0.08),
			cooldown_pulo(0.16),
			cooldown_dano(0.2),
			tempo_morte(4 * 0.45),
			velPulo(-12),
			hitboxAtaque(new sf::RectangleShape(sf::Vector2f(32.0f, 23.0f))),
			velocKnockBack(0.0, 0.0),
			pontos(0),
			id(ident),
			estado_atual(PARADO),
			direcao(0.0, 0.0),
			timer(),
			dt(0.0)
			
		{
			dano = 200;

			veloc.x = 20.0f;
			veloc.y = 0.00;

			num_vidas = 200;

			corpo = new sf::RectangleShape(sf::Vector2f(160.0, 120.0));
			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 105.0, corpo->getSize().y));

			inicializaAnimacoes();
		}

		Jogador::~Jogador()
		{
			std::cout << "deletei o jogador" << std::endl;
			cooldown_ataque = 0.0;
			cooldown_pulo = 0.0;
			cooldown_dano = 0.0;
			velPulo = 0.0;
			if (hitboxAtaque) {
				delete hitboxAtaque;
			}
			hitboxAtaque = nullptr;
			velocKnockBack.x = 0.0;
			velocKnockBack.y = 0.0;
			pontos = 0;
			id = 0;
			estado_atual = PARADO;
			direcao.x = 0.0;
			direcao.y = 0.0;
		}

		void Jogador::colidir(Inimigo* pIn) {
			pIn->danificar(this);
		}

		void Jogador::executar()
		{
			atualizaAnimacao();

			mover();
		}

		void Jogador::salvar()
		{
			nlohmann::json buffer = {};

			salvarDataBuffer(buffer);

			buffer_jogadores.push_back(buffer);
		}

		void Jogador::salvarDataBuffer(nlohmann::json& buffer) {

			Personagem::salvarDataBuffer(buffer);

			buffer["pontos"] = pontos;
			buffer["id"] = id;
			buffer["dt"] = dt;
			buffer["estado_atual"] = estado_atual;
			buffer["direcaoX"] = direcao.x;
			buffer["direcaoY"] = direcao.y;
			buffer["velocKnockBackX"] = velocKnockBack.x;
			buffer["velocKnockBackY"] = velocKnockBack.y;
		}

		void Jogador::carregar(const nlohmann::json& j) {

			pontos = j.at("pontos").get<int>();
			id = j.at("id").get<int>();
			dt = j.at("dt").get<float>();
			estado_atual = static_cast<Entidades::Personagens::Jogador::Estado>(j.at("estado_atual").get<int>());
			direcao.x = j.at("direcaoX").get<float>();
			direcao.y = j.at("direcaoY").get<float>();
			velocKnockBack.x = j.at("velocKnockBackX").get<float>();
			velocKnockBack.y = j.at("velocKnockBackY").get<float>();

			timer.restart();

			Personagem::carregar(j);
		}

		void Jogador::mover() {
			if (ATORDOADO != estado_atual) {
				if (PREPARANDO_PULO != estado_atual) {
					//primeiro "calculamos" a velocidade e depois a aplicamos no movimento...

					sf::Vector2f velocFinal(0.0, 0.0);
					float limiarStun = 0.5; //serve para impedir que o jogador se mova ao colidir (cm um inimigo!)

					if (abs(velocKnockBack.x) < limiarStun) {

						velocFinal.x += veloc.x * direcao.x; //a direcao é setada no set, que é chamado lá no gerenciador de eventos.

					}

					if (abs(velocKnockBack.y) < limiarStun) {

						velocFinal.y += veloc.y * direcao.y;

					}


					velocFinal.x += velocKnockBack.x;
					velocFinal.y += velocKnockBack.y;

					if(corpo) {
						corpo->move(velocFinal);
					}
					else {
						std::cerr << "ERRO: Nao eh possivel mover o corpo pois ele eh NULL" << std::endl;
					}
					
					if (hitBox) {
						hitBox->move(velocFinal);
					}
					else {
						std::cerr << "ERRO: Nao eh possivel mover o corpo pois ele eh NULL" << std::endl;
					}

					//aplicamos um "atrito" aqui! (valor menor que 1, portanto, irá diminuir a cada chamada do mover)

					float atrito = 0.96f;

					velocKnockBack.x *= atrito;
					velocKnockBack.y *= atrito;

					//para não processar infinitamente, zeramos a velocidade do empurrão se ela já for mto pequena.

					if (abs(velocKnockBack.x) < 0.1f) { velocKnockBack.x = 0; }
					if (abs(velocKnockBack.y) < 0.1f) { velocKnockBack.y = 0; }
				}
			}
		}

		void Jogador::setVelKnockBack(sf::Vector2f velKB)
		{
			velocKnockBack = velKB;
		}

		void Jogador::setDirecao(sf::Vector2f dir)
		{
			direcao = dir;
		}

		void Jogador::inicializaAnimacoes()
		{
			setAnimador(corpo);

			if (animador) {

				if (id == 1) //settando as texturas para o jogador 1...
				{
					//Animações em loop

					animador->addAnimacao("Imagens/Samurai_shinobiPack/Idle.png", "Parado", 6, 0.20, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Samurai_shinobiPack/Walk.png", "Andando", 8, 0.12, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Samurai_shinobiPack/Run.png", "Correndo", 8, 0.10, sf::Vector2f(1.0, 1.0));

					//Animações que só devem rodar uma vez

					animador->addAnimacao("Imagens/Samurai_shinobiPack/Jump.png", "Subindo", 12, cooldown_pulo, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Samurai_shinobiPack/Attack_1.png", "Ataque1", 6, cooldown_ataque, sf::Vector2f(1.0, 1.0));
					//animador->addAnimacao("Imagens/Shinobi/Attack_2.png", "Ataque2", 3, cooldown_ataque, sf::Vector2f(1.0, 1.0));
					//animador->addAnimacao("Imagens/Shinobi/Attack_3.png", "Ataque3", 4, 0.18, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Samurai_shinobiPack/Dead.png", "Derrotado", 3, 0.45, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Samurai_shinobiPack/Hurt.png", "Ferido", 2, cooldown_dano, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Samurai_shinobiPack/Shield.png", "Protegendo", 2, 0.10, sf::Vector2f(1.0, 1.0));
				}

				if (id == 2) //settando as texturas para o jogador 2...
				{
					animador->addAnimacao("Imagens/Shinobi/Idle.png", "Parado", 6, 0.20, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Shinobi/Walk.png", "Andando", 8, 0.12, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Shinobi/Run.png", "Correndo", 8, 0.10, sf::Vector2f(1.0, 1.0));

					//Animações que só devem rodar uma vez

					animador->addAnimacao("Imagens/Shinobi/Jump.png", "Subindo", 12, cooldown_pulo, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Shinobi/Attack_1.png", "Ataque1", 5, cooldown_ataque, sf::Vector2f(1.0, 1.0));
					//animador->addAnimacao("Imagens/Shinobi/Attack_2.png", "Ataque2", 3, cooldown_ataque, sf::Vector2f(1.0, 1.0));
					//animador->addAnimacao("Imagens/Shinobi/Attack_3.png", "Ataque3", 4, 0.18, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Shinobi/Dead.png", "Derrotado", 4, tempo_morte / 4, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Shinobi/Hurt.png", "Ferido", 2, cooldown_dano, sf::Vector2f(1.0, 1.0));
					animador->addAnimacao("Imagens/Shinobi/Shield.png", "Protegendo", 4, 0.10, sf::Vector2f(1.0, 1.0));
				}

			}
			else {
				std::cerr << "ERRO: Nao eh possivel inicializar a animacao pois o animado eh NULL" << std::endl;
			}

		}

		void Jogador::atualizaAnimacao()
		{
			// Como todas as animacoes podem mudar de direcaoo, começa setando aqui
			if (direcao.x < 0) {
				paraEsq = true;
			}
			else if (direcao.x > 0) {
				paraEsq = false;
			}

			if (animador) {
				// Atualizacoes segundo o aestado atual
				if (MORRENDO == estado_atual) {	// Prioridade, por isso estah aqui (estah no personagem)
					animador->atualizarAnimJog(false, false, paraEsq, true, "Derrotado"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
				}

				else if (FERIDO == estado_atual && dt < 3 * cooldown_dano) {	// Para a animacao e volta ao normal quando os 3 frames foram desenhados
					animador->atualizarAnimJog(false, false, paraEsq, true, "Ferido");
					dt += timer.getElapsedTime().asSeconds();
					timer.restart();	// Dei restar pra poder congelar o tempo no save
				}

				else if (FERIDO == estado_atual && dt >= 3 * cooldown_dano) {
					estado_atual = PARADO;
				}

				else if (ATACANDO == estado_atual && dt < 4 * cooldown_ataque) {
					atualizarHitboxAtaque(); // posiciona a hitbox de ataque

					animador->atualizarAnimJog(false, false, paraEsq, false, "Ataque1");
					dt += timer.getElapsedTime().asSeconds();
					timer.restart();
				}

				else if (ATACANDO == estado_atual && dt >= 4 * cooldown_ataque) {
					estado_atual = PARADO;
				}

				else if (PREPARANDO_PULO == estado_atual || PULANDO == estado_atual) {	// Quarta prioridade eh o salto	

					dt += timer.getElapsedTime().asSeconds();
					timer.restart();

					if (dt >= 3 * cooldown_pulo && PREPARANDO_PULO == estado_atual) {	// Espera os 3 frames pois eh o agachamento da animacao do pulo
						estado_atual = PULANDO;
						veloc.y = velPulo;	// Velocidade inicial do salto
					}
					animador->atualizarAnimJog(false, false, paraEsq, true, "Subindo"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
				}

				else if (DEFENDENDO == estado_atual) {	// Quinta prioridade eh a defesa
					animador->atualizarAnimJog(false, false, paraEsq, false, "Protegendo");
				}

				// Caminhada, corrida e parado
				else if (direcao.x == 0 && direcao.y == 0) {
					animador->atualizarAnimJog(false, false, paraEsq, false, "Parado"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
				}

				else if (direcao.x != 0 && direcao.y == 0) {

					if (CORRENDO == estado_atual) {
						animador->atualizarAnimJog(false, false, paraEsq, false, "Correndo"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
					}

					else {
						animador->atualizarAnimJog(false, false, paraEsq, false, "Andando"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
					}
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel atualizar a animacao pois o animador eh NULL" << std::endl;
			}
		}

		void Jogador::atualizarHitboxAtaque() {
			if (corpo) {
				if (hitboxAtaque) {
					if (paraEsq) {
						// posiciona à esquerda do jogador
						hitboxAtaque->setPosition(
							corpo->getPosition().x + 42.0f,
							corpo->getPosition().y + 35.0f
						);
					}
					else {
						// posiciona à direita do jogador
						hitboxAtaque->setPosition(
							corpo->getPosition().x + corpo->getSize().x - 75.0f,
							corpo->getPosition().y + 35.0f
						);
					}
				}
				else {
					std::cerr << "ERRO: Nao eh possivel atualizar a hit box de ataque pois ela eh NULL" << std::endl;
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel atualizar a hit box de ataque pois o corpo eh NULL" << std::endl;
			}
		}

		void Jogador::setAtordoado(bool atordoar) {
			if(atordoar) {
				estado_atual = ATORDOADO;
			}
			else {
				estado_atual = PARADO;
			}

		}

		void Jogador::correr(bool correr) {
			if (PULANDO != estado_atual) {
				if (correr) {
					estado_atual = CORRENDO;
					veloc.x = 7.0f;
				}
				else {
					estado_atual = PARADO;
					veloc.x = 20.0f;
				}
			}
		}

		void Jogador::atacar() {
			timer.restart();
			dt = 0;
			estado_atual = ATACANDO;

		}

		bool Jogador::getAtacando() {
			if (ATACANDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

		void Jogador::pular() {
			if (PULANDO != estado_atual && PREPARANDO_PULO != estado_atual) {
				estado_atual = PREPARANDO_PULO;
				timer.restart();
				dt = 0;
			}
		}

		// Zera tudo relacionado ao movimento vertical e aplica a forca normal
		void Jogador::setNoChao() {
			veloc.y = 0.0;
			if (PULANDO == estado_atual) {
				estado_atual = PARADO;
			}
		}

		bool Jogador::getSubindo() {	// Usado no Gerenciador de Eventos
			if (PULANDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

		void Jogador::setDefesa(bool defender) {
			if (defender) {
				estado_atual = DEFENDENDO;
			}
		}

		bool Jogador::protegendo() {
			if (DEFENDENDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}
		
		void Jogador::diminuiVida(float dano) {
			if (MORRENDO != estado_atual) {
				if (DEFENDENDO != estado_atual) {
					if (num_vidas - dano < 0) {
						num_vidas -= num_vidas;
					}
					else if (num_vidas > 0) {
						num_vidas -= dano;
						if (0 != num_vidas) {
							ferir();
						}
					}
					if (0 == num_vidas) {
						estado_atual = MORRENDO;
						dt = 0;
						timer.restart();
					}
				}
			}
			std::cout << num_vidas << std::endl;
		}

		// Dá um pulinho pro lado quando toma dano
		void Jogador::ferir() {
			if (corpo) {
				if (hitBox) {
					float dx;
					if (paraEsq) {
						dx = 30.0;
					}
					else {
						dx = -30.0;
					}
					corpo->move(dx, 0.0);
					hitBox->move(dx, 0.0);

					estado_atual = FERIDO;
					timer.restart();
					dt = 0.0;
				}
				else {
					std::cerr << "ERRO: Nao eh possivel ferir pois o hit box eh NULL" << std::endl;
				}
			}
			else {
				std::cerr << "ERRO: Nao eh possivel ferir pois o corpo eh NULL" << std::endl;
			}
		}

		sf::RectangleShape* Jogador::getHitboxAtaque() const {
			return hitboxAtaque;
		}

		void Jogador::morrer() {
			estado_atual = MORRENDO;
		}

		bool Jogador::getFerido() {
			if (FERIDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

		bool Jogador::getMorto() {
			if (MORRENDO == estado_atual) {
				return true;
			}
			else {
				return false;
			}
		}

		int Jogador::getPontuacao() {
			return pontos;
		}

		void Jogador::aumentaPontuacao(int num) {
			pontos += num;
		}

		bool Jogador::podeSeguirPorMorte() {
			dt += timer.getElapsedTime().asSeconds();
			timer.restart();
			if (MORRENDO == estado_atual && dt >= tempo_morte) {
				return false;
			}
			return true;
		}

	}

}



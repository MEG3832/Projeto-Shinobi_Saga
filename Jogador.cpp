#include "Jogador.h"
#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		Jogador::Jogador(const sf::Vector2f pos, int ident) :
			Personagem(),
			veloc(0.10, 0.10),	// Isso eh uma boa velocidade?
			velocKnockBack(0.0, 0.0),
			pontos(0),
			id(ident),
			direcao(0.0, 0.0),
			caindo(false),
			subindo(false),
			paraEsq(false),
			atordoado(false),
			correndo(false),
			atacando(false)
		{
			corpo = new sf::RectangleShape(sf::Vector2f(100.0, 160.0));
			corpo->setPosition(pos);

			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Jogador::Jogador() :
			Personagem(),
			veloc(0.08, 0.08),
			velocKnockBack(0.0, 0.0),
			pontos(0),
			id(1),
			direcao(0.0, 0.0),
			caindo(false),
			subindo(false),
			paraEsq(false),
			atordoado(false),
			correndo(false),
			atacando(false),
			dt(0),
			timer(),
			cooldown_ataque(4 * 0.10)
		{
			num_vidas = 100;

			corpo = new sf::RectangleShape(sf::Vector2f(150.0, 120.0));
			corpo->setPosition(0.0, ALTURA_TELA - 50 - corpo->getSize().y);

			hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize().x - 105.0, corpo->getSize().y));
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x/2 - hitBox->getSize().x/2),
								corpo->getPosition().y);

			inicializaAnimacoes();
		}

		Jogador::~Jogador()
		{
			veloc.x = 0;
			veloc.y = 0;
			pontos = -1;
			id = 0;
			direcao = sf::Vector2f(0.0, 0.0);
			paraEsq = false;
			subindo = false;
			caindo = false;
		}

		void Jogador::colidir(Inimigo* pIn) {
			pIn->danificar(this);
		}

		void Jogador::executar()
		{
			atualizaAnimacao();
		}

		void Jogador::salvar()
		{
			return;
		}

		void Jogador::mover() {
			if (!atordoado) {
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

				corpo->move(velocFinal);
				hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
									corpo->getPosition().y);

				//aplicamos um "atrito" aqui! (valor menor que 1, portanto, irá diminuir a cada chamada do mover)

				float atrito = 0.99f;

				velocKnockBack.x *= atrito;
				velocKnockBack.y *= atrito;

				//para não processar infinitamente, zeramos a velocidade do empurrão se ela já for mto pequena.

				if (abs(velocKnockBack.x) < 0.1f) { velocKnockBack.x = 0; }
				if (abs(velocKnockBack.y) < 0.1f) { velocKnockBack.y = 0; }
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

			//Animações em loop

			animador->addAnimacao("Imagens/Fighter/Idle.png", "Parado", 6, 0.20, sf::Vector2f(1.0, 1.0));
			animador->addAnimacao("Imagens/Fighter/Walk.png", "Andando", 8, 0.12, sf::Vector2f(1.0, 1.0));
			animador->addAnimacao("Imagens/Fighter/Run.png", "Correndo", 8, 0.1, sf::Vector2f(2.5, 1.0));

			//Animações de pulo

			animador->addAnimacao("Imagens/Fighter/Jump.png", "Subindo", 10, 0.2, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Fighter/Jump.png", "Descendo", 10, 0.2, sf::Vector2f(2.5, 1.0));

			//Animações que só devem rodar uma vez

			animador->addAnimacao("Imagens/Fighter/Attack_1.png", "Ataque1", 4, 0.10, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Fighter/Attack_2.png", "Ataque2", 3, 0.12, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Fighter/Attack_3.png", "Ataque3", 4, 0.18, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Fighter/Dead.png", "Derrotado", 3, 0.45, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Fighter/Hurt.png", "Ferido", 3, 0.17, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Fighter/Shield.png", "Protegendo", 2, 0.17, sf::Vector2f(2.5, 1.0));

		}

		void Jogador::atualizaAnimacao()
		{
			bool rodaUmaVez;

			if(atacando && dt < cooldown_ataque) {
				rodaUmaVez = true;
				animador->atualizarAnimJog(caindo, subindo, paraEsq, rodaUmaVez, "Ataque1");
				dt = timer.getElapsedTime().asSeconds();
			}
			else {
				rodaUmaVez = false;
				atacando = false;

				if (direcao.x == 0 && direcao.y == 0) {
					animador->atualizarAnimJog(caindo, subindo, paraEsq, rodaUmaVez, "Parado"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
				}
				else if (direcao.x != 0 && direcao.y == 0) {
					if (direcao.x < 0) {
						paraEsq = true;
					}
					else {
						paraEsq = false;
					}

					if (correndo) {
						animador->atualizarAnimJog(caindo, subindo, paraEsq, rodaUmaVez, "Correndo"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
					}
					else {
						animador->atualizarAnimJog(caindo, subindo, paraEsq, rodaUmaVez, "Andando"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
					}
				}
			}
		}

		void Jogador::setAtordoado(bool atordoar) {
			atordoado = atordoar;
		}

		void Jogador::correr(bool correr) {
			correndo = correr;
		}

		void Jogador::atacar() {
			timer.restart();
			dt = 0;
			atacando = true;
		}

		bool Jogador::getAtacando() {
			return atacando;
		}

	}

}



#include "Jogador.h"
#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		Jogador::Jogador(const sf::Vector2f pos, int ident) :
			Personagem(),
			veloc(0.10f, 0.10f),	// Isso eh uma boa velocidade?
			velocKnockBack(0.0f, 0.0f),
			pontos(0),
			id(ident),
			direcao(),
			caindo(false),
			subindo(false),
			paraEsq(false)
		{
			corpo = new sf::RectangleShape(sf::Vector2f(90.0f, 140.0f));
			setAnimador(corpo);
			inicializaAnimacoes();
		}

		Jogador::Jogador() :
			Personagem(),
			veloc(0.10f, 0.10f),
			velocKnockBack(0.0f, 0.0f),
			pontos(0),
			id(1),
			direcao(),
			caindo(false),
			subindo(false),
			paraEsq(false)
		{
			corpo = new sf::RectangleShape(sf::Vector2f(100.0f, 160.0f));
			corpo->setPosition(0.0, ALTURA_TELA - 50 - corpo->getSize().y);
			setAnimador(corpo);
			inicializaAnimacoes();

		}

		Jogador::~Jogador()
		{
			veloc.x = 0;
			veloc.y = 0;
			pontos = -1;
			id = 0;
			direcao = 0;
			paraEsq = false;
			subindo = false;
			caindo = false;
		}

		void Jogador::colidir(Inimigo* pIn) {
			pIn->danificar(this);
		}

		void Jogador::executar()
		{
			return;
		}

		void Jogador::salvar()
		{
			return;
		}

		void Jogador::mover() {

			//primeiro "calculamos" a velocidade e depois a aplicamos no movimento...

			sf::Vector2f velocFinal(0.0f, 0.0f);
			float limiarStun = 0.5f; //serve para impedir que o jogador se mova ao colidir (cm um inimigo!)

			if (corpo) {

				if (abs(velocKnockBack.x) < limiarStun) {

					if ('D' == direcao)
					{
						velocFinal.x += veloc.x;
					}

					if ('E' == direcao)
					{

						velocFinal.x -= veloc.x;
					}

					
				}

				if (abs(velocKnockBack.y) < limiarStun) {

					if ('B' == direcao)
					{
						velocFinal.y += veloc.y;
					}

					if ('C' == direcao)
					{
						velocFinal.y -= veloc.y;
					}

				}
				

				velocFinal.x += velocKnockBack.x;
				velocFinal.y += velocKnockBack.y;

				corpo->move(velocFinal);

				//aplicamos um "atrito" aqui! (valor menor que 1, portanto, irá diminuir a cada chamada do mover)

				float atrito = 0.99f;

				velocKnockBack.x *= atrito;
				velocKnockBack.y *= atrito;

				//para não processar infinitamente, zeramos a velocidade do empurrão se ela já for mto pequena.

				if (abs(velocKnockBack.x) < 0.1f) { velocKnockBack.x = 0; }
				if (abs(velocKnockBack.y) < 0.1f) { velocKnockBack.y = 0; }

			}
			else {
				std::cerr << "ERRO: Nao foi possivel encontrar o corpo pois ele eh NULL" << std::endl;
			}
		}

		void Jogador::diminuiVida(int nv_maldade)
		{
			int dano = nv_maldade;

			num_vidas -= dano;

		}

		int Jogador::getVida()
		{
			return num_vidas;
		}

		void Jogador::setVelKnockBack(sf::Vector2f velKB)
		{
			velocKnockBack = velKB;
		}

		void Jogador::setDirecao(const char direcao) {
			this->direcao = direcao;
		}

		char Jogador::getDirecao() {
			return direcao;
		}

		void Jogador::inicializaAnimacoes()
		{
			//Animações em loop

			animador->addAnimacao("Imagens/Samurai/Idle_2.png", "Parado", 6, 0.20f, sf::Vector2f(2.5, 1.0));
			animador->addAnimacao("Imagens/Samurai/Walk.png", "Andando", 9, 0.12f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Run.png", "Correndo", 8, 0.1f, sf::Vector2f(6.0, 2.0));

			//Animações de pulo

			animador->addAnimacao("Imagens/Samurai/Jump.png", "Subindo", 9, 0.2f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Jump.png", "Descendo", 9, 0.2f, sf::Vector2f(6.0, 2.0));

			//Animações que só devem rodar uma vez

			animador->addAnimacao("Imagens/Samurai/Attack_1.png", "Ataque1", 4, 0.16f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Attack_2.png", "Ataque2", 5, 0.12f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Attack_3.png", "Ataque3", 4, 0.18f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Dead.png", "Derrotado", 6, 0.45f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Hurt.png", "Ferido", 3, 0.17f, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Protection.png", "Protegendo", 2, 0.17f, sf::Vector2f(6.0, 2.0));

		}

		void Jogador::atualizaAnimacao()
		{
			bool rodaUmaVez = false;


			//terminar: fazer uma animação de cada estado de acordo com o valor de caindo, subindo, velocidade, se está no chão ou não...
			//vamos fazer as partes dos botões dentro de Jogador mesmo?

			//botão -> move o corpo e muda a animação 


			//teste:
			animador->atualizarAnimJog(caindo, subindo, paraEsq, rodaUmaVez, "Parado"); //quando eu atualizo a animação, preciso saber se está caindo, subindo ou nenhum dos dois!
		}

	}

}

// atributos estáticos:


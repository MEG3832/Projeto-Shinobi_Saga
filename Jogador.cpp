#include "Jogador.h"

namespace Entidades {

	namespace Personagens {

		Jogador::Jogador(const sf::Vector2f pos, int ident) :
			Personagem(),
			veloc(0.04f, 0.04f),
			pontos(0),
			id(ident),
			direcao(),
			caindo(false),
			subindo(false),
			paraEsq(false)
		{
			corpo = new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
		}




		Jogador::Jogador() :
			Personagem(),
			veloc(0.04f, 0.04f),
			pontos(0),
			id(1),
			direcao()
		{
			corpo = new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
		}


		Jogador::~Jogador()
		{
			veloc.x = 0;
			veloc.y = 0;
			pontos = -1;
			id = 0;
		}

		const sf::RectangleShape* Jogador::getCorpo() {
			return corpo;
		}

		void Jogador::colidir(Entidade* pe) {
			std::cout << "Colidiu" << std::endl;
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
			if (corpo) {
				if ('D' == direcao)
				{
					corpo->move(veloc.x, 0.0);
				}

				if ('C' == direcao)
				{
					corpo->move(0.0, -veloc.y);
				}

				if ('B' == direcao)
				{
					corpo->move(0.0, veloc.y);
				}

				if ('E' == direcao)
				{
					corpo->move(-veloc.x, 0.0);
				}
			}
			else {
				std::cerr << "ERRO: Nao foi possivel encontrar o corpo pois ele eh NULL" << std::endl;
			}
		}

		void Jogador::setDirecao(const char direcao) {
			this->direcao = direcao;
		}

		void Jogador::inicializaAnimacoes()
		{
			//Animações em loop

			animador->addAnimacao("Imagens/Samurai/Idle.png", "Parado", 6, 0.20, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Walk.png", "Andando", 9, 0.12, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Run.png", "Correndo", 8, 0.1, sf::Vector2f(6.0, 2.0));

			//Animações de pulo

			animador->addAnimacao("Imagens/Samurai/Jump.png", "Subindo", 9, 0.2, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Jump.png", "Descendo", 9, 0.2, sf::Vector2f(6.0, 2.0));

			//Animações que só devem rodar uma vez

			animador->addAnimacao("Imagens/Samurai/Attack_1.png", "Ataque1", 4, 0.16, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Attack_2.png", "Ataque2", 5, 0.12, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Attack_3.png", "Ataque3", 4, 0.18, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Dead.png", "Derrotado", 6, 0.45, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Hurt.png", "Ferido", 3, 0.17, sf::Vector2f(6.0, 2.0));
			animador->addAnimacao("Imagens/Samurai/Protection.png", "Protegendo", 2, 0.17, sf::Vector2f(6.0, 2.0));

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


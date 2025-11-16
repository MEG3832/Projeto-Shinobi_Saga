#include "Projetil.h"
#include "Kitsune.h"
//#include "Jogador.h"

namespace Entidades {

	Projetil::Projetil(Personagens::Kitsune* pKits) :
		Entidade(),
		pKitsune(pKits),
		ativo(false)
	{
		corpo = new sf::RectangleShape(sf::Vector2f(30.0f, 45.0f));
		corpo->setPosition(pKitsune->getPos());	// seta a posicao do projetil igual a posicao da kitsune....

		hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize()));
		hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
			corpo->getPosition().y);


		setAnimador(corpo);
		inicializaAnimacoes();

	}

	Projetil::~Projetil() {
		ativo = false;
	}

	void Projetil::setEstadoProj(bool estado)
	{
		ativo = estado;
		
	}

	bool Projetil::getEstadoProj()
	{
		return ativo;
	}


	void Projetil::setVelocidade(sf::Vector2f vel) {
		veloc = vel;
	}

	void Projetil::danificar(Personagens::Jogador* pJ)
	{
		if (pJ && ativo) {
			int dano_projetil = 20;
			pJ->diminuiVida(dano_projetil);

			std::cout << "Projetil acertou! Vida Jogador: " << pJ->getVida() << std::endl;

			// desativa o projétil ao colidir
			setEstadoProj(false);
		}
	}

	void Projetil::executar() {

		//verifica o estado do projétil.

		if (ativo)
		{
			corpo->setFillColor(sf::Color::White); // deixa o projétil "visível" (cor branca para aparecer a textura)

			if (veloc.x < 0) // se a velocidade de x dele é negativa, então é porque ele foi ativado para a esquerda
			{
				animador->atualizarAnimProjetil(true, "Fogo");
			}

			else
				animador->atualizarAnimProjetil(false, "Fogo");

			
			corpo->move(veloc);
			hitBox->setPosition(corpo->getPosition());

			// pega o retângulo do projétil
			sf::FloatRect projetilBounds = corpo->getGlobalBounds();

			// pega o retângulo da câmera (View)
			sf::View camera = pGG->getWindow()->getView();
			sf::FloatRect cameraBounds(camera.getCenter() - camera.getSize() / 2.f, camera.getSize());

			// verifica se o projétil NÃO está mais tocando a câmera
			if (!cameraBounds.intersects(projetilBounds))
			{
				setEstadoProj(false);
			}

				//a "desativação" do projétil quando atinge o jogador já eh tratada na colisão (dê uma olhada em danificar, o método anterior!)

		}

		else
		{
			corpo->setFillColor(sf::Color::Transparent); //cor "invisível"
			corpo->setPosition(pKitsune->getPos().x + 50.0f, pKitsune->getPos().y + 75.0f); //projétil fica mais retraído, mais próximo da kitsune
			hitBox->setPosition(corpo->getPosition());
		}


	}

	void Projetil::salvar() {
		return;
	}

	void Projetil::inicializaAnimacoes()
	{
		//a animação do projétil só vai rodar uma vez.

		animador->addAnimacao("Imagens/Projetil_Fogo/Fire_2.png", "Fogo", 11, 0.1f, sf::Vector2f(1.0, 1.0));
	}

}
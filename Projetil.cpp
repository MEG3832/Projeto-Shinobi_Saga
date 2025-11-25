#include "Projetil.h"
#include "Kitsune.h"
//#include "Jogador.h"

namespace Entidades {

	Projetil::Projetil(Personagens::Kitsune* pKits) :
		Entidade(),
		pKitsune(pKits),
		ativo(false)
	{
		corpo = new sf::RectangleShape(sf::Vector2f(90.0f, 90.0f));
		if (corpo) {
			corpo->setPosition(pKitsune->getCorpo()->getPosition());	// seta a posicao do projetil igual a posicao da kitsune....
			setAnimador(corpo);
		}

		hitBox = new sf::RectangleShape(sf::Vector2f(corpo->getSize()));
		if (hitBox) {
			hitBox->setPosition(corpo->getPosition().x + (corpo->getSize().x / 2 - hitBox->getSize().x / 2),
								corpo->getPosition().y);
		}

		inicializaAnimacoes();

	}

	Projetil::~Projetil() {
		ativo = false;
		pKitsune = nullptr;
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
		if (pKitsune) {
			if (pJ && ativo) {
				int dano_projetil = (pKitsune->getNvMaldade()) * 20;
				pJ->diminuiVida(dano_projetil);
				pKitsune->aumentaNvMaldade();

				// desativa o projétil ao colidir
				setEstadoProj(false);
			}
		}
	}

	void Projetil::executar() {

		if (corpo && hitBox && animador) {

			//verifica o estado do projétil.
			if (ativo)
		git l	{
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
				corpo->setPosition(pKitsune->getCorpo()->getPosition().x + 70.0f, pKitsune->getCorpo()->getPosition().y + 75.0f); //projétil fica mais retraído, mais próximo da kitsune
				hitBox->setPosition(corpo->getPosition());
			}

			sofrerContraForca();
		}
	}

	void Projetil::salvar() {
		nlohmann::json buffer = {};

		salvarDataBuffer(buffer);

		buffer_projeteis.push_back(buffer);
	}

	void Projetil::salvarDataBuffer(nlohmann::json& buffer) {

		Entidade::salvarDataBuffer(buffer);

		buffer["ativo"] = ativo;
	}

	void Projetil::carregar(const nlohmann::json& j) {

		try {
			ativo = j.at("ativo").get<bool>();
		}
		catch (const nlohmann::json::out_of_range& e) {
			std::cerr << "ERRO: Alguma das chaves estah ausente." << e.what() << std::endl;
		}

		Entidade::carregar(j);
	}

	void Projetil::inicializaAnimacoes()
	{
		if (animador) {
			//a animação do projétil só vai rodar uma vez.

			animador->addAnimacao("Imagens/Projetil_Fogo/Fire_2.png", "Fogo", 11, 0.1f, sf::Vector2f(1.0, 1.0));

			animador->atualizarAnimProjetil(true, "Fogo");
		}
	}

	void Projetil::sofrerContraForca() {
		veloc.y = 0;
		veloc.y -= GRAVIDADE;
	}

}
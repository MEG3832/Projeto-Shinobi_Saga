#include "Fundo.h"

namespace Parallax {

	Fundo::Camada::Camada(sf::Vector2f tam, sf::Texture textura, const float vel) :
		tam(tam),
		textura(textura),
		dimensao(0, 0, 0, 0),
		vel(vel)
	{
		// Delimita o tamanho da textura
		dimensao.width = -std::abs(static_cast<float>(textura.getSize().x));
		dimensao.height = static_cast<float>(textura.getSize().y);
		dimensao.left = static_cast<float>(textura.getSize().x);

		// Dá o tamanho do fundo, sua posição inicial e seta a sua textura
		fundo.setSize(tam);
		fundo.setTexture(&this->textura);
		fundo.setPosition(0.0f, 0.0f);

		fundoAuxiliar.setSize(tam);
		fundoAuxiliar.setTexture(&this->textura);
		fundoAuxiliar.setPosition(tam.x, 0.0f);
	}

	Fundo::Camada::~Camada()
	{}

	// A textura principal vira a auxiliar e vice-versa
	void Fundo::Camada::trocarTextura() {
		sf::RectangleShape temp = fundo;
		fundo = fundoAuxiliar;
		fundoAuxiliar = temp;
	}

	void Fundo::Camada::desenharCamada(sf::RenderWindow* window) {
		if(pGG) {
			pGG->desenharRect(fundo);
			if (vel) {
				pGG->desenharRect(fundoAuxiliar);
			}
		}
		else {
			std::cerr << "ERRO: nao eh possivel desenhar as camadas pois o Gerenciador Grafico eh NULL" << std::endl;
		}
	}

	// Atualiza a posição dos fundo de acordo com o movimento realizado
	void Fundo::Camada::atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual) {
		sf::Vector2f posFundo = fundo.getPosition();
		sf::Vector2f posFundoAux = fundoAuxiliar.getPosition();
		const float dx = ds.x * 0.5f;	// Suaviliza o movimento em x
		const float posDireita = posCameraAtual.x + tam.x / 2.0f;
		const float posEsquerda = posCameraAtual.x - tam.x / 2.0f;

		if (vel) {	// Se está se movendo
			// Movimenta os fundos em um dx
			fundo.move(dx * -vel, 0.0f);
			fundoAuxiliar.move(dx * -vel, 0.0f);


			if (ds.x > 0.0f) {	// Câmera está se movendo para a direita
				if (posFundo.x + tam.x < posEsquerda) {	// Se o fundo principal foi para trás da borda esquerda, troca com o fundo auxiliar
					trocarTextura();
					fundo.setPosition(posEsquerda, posFundo.y);
					fundoAuxiliar.setPosition(posDireita, posFundoAux.y);
				}
			}
			// trocar depois para uma comparação com a borda direita
			else {
				if (posFundo.x > posEsquerda) {	// O fundo começou a ultrapassar a borda direita
					trocarTextura();
					fundo.setPosition(posEsquerda - tam.x, posFundo.y);
					fundoAuxiliar.setPosition(posEsquerda, posFundoAux.y);
				}
			}
		}
		else {	// Se está parado
			fundo.setPosition(posEsquerda, posFundo.y);
		}
	}

	Fundo::Fundo() :
		Ente(),
		posAnteriorCamera(0, 0)
	{	
		if (pGG) {
			posAnteriorCamera = pGG->getCamera().getCenter();
		}
		else {
			std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
		}

		camadas.clear();
		// cada fase tem seu próprio fundo
	}

	Fundo::~Fundo() {	// Dá´pra adicionar um iterador aqui (padrão de projeto)
		for (int i = 0; i < camadas.size(); i++) {
			Camada* camada = camadas[i];
			if (camada) {
				delete(camada);
				camada = nullptr;
			}
			else {
				std::cerr << "EROO: A camada " << i << " eh NULL" << std::endl;
			}
		}
		camadas.clear();

	}

	// Atualiza a posição de cada uma das camadas e desenha elas
	void Fundo::executar() {
		if (pGG) {
			sf::Vector2f posCamera = pGG->getCamera().getCenter();
			sf::Vector2f ds = posCamera - posAnteriorCamera;
			posAnteriorCamera = posCamera;

			for (int i = 0; i < (int)camadas.size(); i++) {
				if (camadas[i]) {
					camadas[i]->atualizar(ds, posCamera);
				}
				else {
					std::cerr << "ERRO: A camada " << i << " eh NULL" << std::endl;
				}
			}

			desenhar();
		}
		else {
			std::cerr << "ERRO: O Gerenciador Grafico eh NULL" << std::endl;
		}
	}

	void Fundo::desenhar() {	// Dá pra adicionar iterator aqui (padrão de projeto)
		for (int i = 0; i < (int)camadas.size(); i++) {
			if (camadas[i]) {
				if (pGG) {
					camadas[i]->desenharCamada(pGG->getWindow());
				}
				else {
					std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
				}
			}
			else std::cerr << "ERRO: Camadada " << i << " eh NULL" << std::endl;
		}
	}

	void Fundo::addCamada(const sf::Vector2f tam, const float vel, const char* caminhoTextura) {
		if (pGG) {
			Camada* camada = new Camada(tam, pGG->carregarTextura(caminhoTextura), vel);

			camadas.push_back(camada);
		}
		else {
			std::cerr << "ERRO: Nao eh possivel adicionar a cmamada pois o Gerenciador Grafico eh NULL" << std::endl;
		}
	}

}
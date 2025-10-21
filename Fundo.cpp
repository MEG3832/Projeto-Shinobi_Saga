#include "Fundo.h"

Fundo::Fundo() :
	Ente(),
	posAnteriorCamera(0,0)
{	// cada fase tem seu próprio fundo, então isso aqui vai mudar
	if(pGG) {
		posAnteriorCamera = pGG->getCamera().getCenter();
	}
	else {
		std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
	}

	camadas.clear();

	addCamada("Imagens/DarkForest/Camada1.png", 0.05f);
	addCamada("Imagens/DarkForest/Camada2.png", 0.05f);
	addCamada("Imagens/DarkForest/Camada3.png", 0.4f);
	addCamada("Imagens/DarkForest/Chao.png", 0.4f);
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
	for(int i = 0; i < (int)camadas.size(); i++) {
		if(camadas[i]) {
			if(pGG) {
				camadas[i]->desenharCamada(pGG->getWindow());
			}
			else {
				std::cerr << "ERRO: Gerenciador Grafico eh NULL" << std::endl;
			}
		}
		else std::cerr << "ERRO: Camadada " << i << " eh NULL" << std::endl;
	}
}

void Fundo::addCamada(const char* caminhoTextura, const float vel) {
	Camada* camada = new Camada((sf::Vector2f) pGG->getWindow()->getSize(), pGG->carregarTextura(caminhoTextura), vel);
	if (camada) {
		camadas.push_back(camada);
	}
	else {
		std::cerr << "ERRO: nao foi possivel adicionar a camada " << std::endl;
	}
}
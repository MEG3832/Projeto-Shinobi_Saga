#include "Fundo.h"

Fundo::Fundo() :
	Ente(),
	posAnteriorCamera(pGG->getCamera().getCenter())
{	// cada fase tem seu próprio fundo, então isso aqui vai mudar
	addCamada("C:/Users/adils/Documents/Duda/Tec Prog/Game/Game/DarkForest/Camada1.png", 0.0f);
	addCamada("../../DarkForest/Camada2.png", 0.05f);
	addCamada("../../DarkForest/Camada3.png", 0.1f);
	addCamada("../../DarkForest/Chao.png", 0.1f);
}

Fundo::~Fundo() {
	for (int i = 0; i < camadas.size(); i++) {
		Camada* camada = camadas[i];
		if (camada) {
			delete(camada);
			camada = nullptr;
		}
	}
	camadas.clear();

}

void Fundo::executar() {
	if (pGG) {
		sf::Vector2f posCamera = pGG->getCamera().getCenter();
		sf::Vector2f ds = posCamera - posAnteriorCamera;
		posAnteriorCamera = posCamera;
		for (int i = 0; i < (int)camadas.size(); i++)
			if (camadas[i]) {
				camadas[i]->atualizar(ds, posCamera);
			}
		desenhar();
	}
}

void Fundo::desenhar() {	// Dá pra adicionar iterator aqui (padrão de projeto)
	for(int i = 0; i < (int)camadas.size(); i++) {
		if(camadas[i])
			if(pGG) 
				camadas[i]->desenharCamada(pGG->getWindow());
			else 
				std::cerr << "Gerenciador Grafico eh NULL" << std::endl;
		else std::cerr << "Camadada " << i << " eh NULL" << std::endl;
	}
}

void Fundo::addCamada(const char* caminhoTextura, const float vel) {
	Camada* camada = new Camada((sf::Vector2f) pGG->getWindow()->getSize(), pGG->carregarTextura(caminhoTextura), vel);
	if(!camada) {
		std::cerr << "ERRO: nao foi possivel adicionar a camada " << std::endl;
		exit(1);
	}

	camadas.push_back(camada);
}
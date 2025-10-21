#include "Gerenciador_Grafico.h"

Gerenciador_Grafico* Gerenciador_Grafico::pGrafico = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico() :
	window(new sf::RenderWindow(sf::VideoMode(COMPRIMENTO_TELA, ALTURA_TELA), "Nome do Jogo")),
	camera(sf::Vector2f(COMPRIMENTO_TELA / 2, ALTURA_TELA / 2), sf::Vector2f(COMPRIMENTO_TELA, ALTURA_TELA))
{}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
	if (window) {
		delete(window);
		window = nullptr;
	}
}

Gerenciador_Grafico* Gerenciador_Grafico::getGerenciadorGrafico() {
	if (pGrafico == nullptr) {
		pGrafico = new Gerenciador_Grafico();
	}
	return pGrafico;
}

void Gerenciador_Grafico::desenharEnte(sf::CircleShape corpo) {
	window->draw(corpo);
}

void Gerenciador_Grafico::mostrarEntes() {
	window->display();
}

sf::RenderWindow* Gerenciador_Grafico::getWindow() {
	if (!window) {
		std::cout << "ALERTA: window é nullptr em getWindow()!" << std::endl;
	}
	return window;
}

const bool Gerenciador_Grafico::verificaJanelaAberta() {
	return window->isOpen();
}

void Gerenciador_Grafico::limpaJanela() {
	window->clear();
}

void Gerenciador_Grafico::fecharJanela() {
	window->close();
}

sf::View Gerenciador_Grafico::getCamera() {
	return camera;
}

void Gerenciador_Grafico::atualizaCamera(sf::Vector2f pos) {	// O parâmetro é a posição do jogador
	sf::Vector2f center = camera.getCenter();
	center.x = pos.x;        // centro da câmera = posição X do jogador
	camera.setCenter(center);
	window->setView(camera);
}

sf::Texture Gerenciador_Grafico::carregarTextura(const char* caminhoTextura) {
	sf::Texture textura;
	if (!textura.loadFromFile(caminhoTextura)) {
		std::cerr << "ERRO: nao foi possivel encontrar o caminho da textura - " << caminhoTextura << std::endl;
		exit(1);
	}

	return textura;
}
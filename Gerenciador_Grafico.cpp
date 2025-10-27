#include "Gerenciador_Grafico.h"

namespace Gerenciadores {

	Gerenciador_Grafico* Gerenciador_Grafico::pGrafico = nullptr;

	Gerenciador_Grafico::Gerenciador_Grafico() :
		window(new sf::RenderWindow(sf::VideoMode(COMPRIMENTO_TELA, ALTURA_TELA), "Nome do Jogo")),
		camera(sf::Vector2f(COMPRIMENTO_TELA / 2, ALTURA_TELA / 2), sf::Vector2f(COMPRIMENTO_TELA, ALTURA_TELA))
	{}

	Gerenciador_Grafico::~Gerenciador_Grafico()
	{
		if (window) {	// Como a janela foi criada aqui, ela tamb�m � deletada de aqui
			delete(window);
		}
		window = nullptr;
	}

	// Usar isso para usar o gerenciador Gráfico já existente ou criar um novo já não tiver
	Gerenciador_Grafico* Gerenciador_Grafico::getGerenciadorGrafico() {
		if (!pGrafico) {
			pGrafico = new Gerenciador_Grafico();
		}

<<<<<<< HEAD
		return pGrafico;
	}

	void Gerenciador_Grafico::desenharEnte(sf::RectangleShape corpo) {
		if (window) {
			window->draw(corpo);
		}
		else {
			std::cerr << "ERRO: window eh NULL" << std::endl;
		}
	}

	void Gerenciador_Grafico::mostrarEntes() {
		if (window) {
			window->display();
		}
		else {
			std::cerr << "ERRO: window eh NULL" << std::endl;
		}
	}

	sf::RenderWindow* Gerenciador_Grafico::getWindow() {
		return window;
	}

	const bool Gerenciador_Grafico::verificaJanelaAberta() {
		if (window) {
			return window->isOpen();
		}
		else {
			std::cerr << "ERRO: window eh NULL" << std::endl;
			return false;
		}
	}

	void Gerenciador_Grafico::limpaJanela() {
		if (window) {
			window->clear();
		}
		else {
			std::cerr << "ERRO: window eh NULL" << std::endl;
		}
	}

	void Gerenciador_Grafico::fecharJanela() {
		if (window) {
			window->close();
		}
		else {
			std::cerr << "ERRO: window eh NULL" << std::endl;
		}
	}

	sf::View Gerenciador_Grafico::getCamera() {
		return camera;
	}

	void Gerenciador_Grafico::atualizaCamera(sf::Vector2f pos) {	// Move a c�mera com o par�metro (a posi��o do jogador)
		if (window) {
			sf::Vector2f center = camera.getCenter();
			center.x = pos.x;        // centro da c�mera = posi��o X do jogador
			camera.setCenter(center);
			window->setView(camera);
		}
		else {
			std::cerr << "ERRO: window eh NULL" << std::endl;
		}
	}

	sf::Texture Gerenciador_Grafico::carregarTextura(const char* caminhoTextura) {
		sf::Texture textura;

		if (!textura.loadFromFile(caminhoTextura)) {
			std::cerr << "ERRO: nao foi possivel encontrar o caminho da textura - " << caminhoTextura << std::endl;
			exit(1);
		}

		return textura;
=======
void Gerenciador_Grafico::desenharEnte(sf::RectangleShape corpo) {	// N�o faz nada por enquanto
	if(window) {
		window->draw(corpo);
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
	}
}

void Gerenciador_Grafico::mostrarEntes() {
	if(window) {
		window->display();
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
	}
}

sf::RenderWindow* Gerenciador_Grafico::getWindow() {
	return window;
}

const bool Gerenciador_Grafico::verificaJanelaAberta() {
	if(window) {
		return window->isOpen();
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
		return false;
	}
}

void Gerenciador_Grafico::limpaJanela() {
	if(window) {
		window->clear();
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
	}
}

void Gerenciador_Grafico::fecharJanela() {
	if(window) {
		window->close();
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
	}
}

sf::View Gerenciador_Grafico::getCamera() {
	return camera;
}

void Gerenciador_Grafico::atualizaCamera(sf::Vector2f pos) {	// Move a c�mera com o par�metro (a posi��o do jogador)
	if(window) {
		sf::Vector2f center = camera.getCenter();
		center.x = pos.x;        // centro da c�mera = posi��o X do jogador
		camera.setCenter(center);
		window->setView(camera);
	}
	else {
		std::cerr << "ERRO: window eh NULL" << std::endl;
	}
}

sf::Texture Gerenciador_Grafico::carregarTextura(const char* caminhoTextura) {
	sf::Texture textura;

	if (!textura.loadFromFile(caminhoTextura)) {
		std::cerr << "ERRO: nao foi possivel encontrar o caminho da textura - " << caminhoTextura << std::endl;
		exit(1);
>>>>>>> animation
	}

}
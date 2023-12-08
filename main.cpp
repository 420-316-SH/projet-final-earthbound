#include <SFML/Graphics.hpp>
#include "game.h"

using namespace sf;

int main() {
	RenderWindow window(VideoMode(720, 720), "Titre de la fenêtre");
	Event event;
	RectangleShape fondEcran;
	
	// Ajout Antho pour test
	Game earthbound;
	earthbound.init( -2150,  -190,  3000,  3328, "img/bgMap.png");
	

	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(earthbound.getBG());
		window.display();
	}

	return 0;
}

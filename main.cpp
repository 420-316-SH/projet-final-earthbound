#include <SFML/Graphics.hpp>
#include "game.h"

using namespace sf;

int main() {
	RenderWindow window(VideoMode(1280, 720), "Titre de la fenêtre");
	Event event;
	RectangleShape fondEcran;

	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(fondEcran);
		window.display();
	}

	return 0;
}

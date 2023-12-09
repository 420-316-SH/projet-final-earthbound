#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "entite.h"
#include "joueur.h"
#include "Game.h"

using namespace sf;
void Game::init(int posX, int posY, int w, int h, const char* nomSprite)
{
	_fondEcranPlay.setPosition(posX, posY);
	_fondEcranPlay.setSize(Vector2f(w, h));
	if (!_textureBgMap.loadFromFile("img/bgMap.png"))
	{
		exit(1);
	}
	_fondEcranPlay.setTexture(&_textureBgMap);
	//_ness.s
}

void Game::play()
{
	init(0, 0, 3000, 3328, "img/bgMap.png");
	RenderWindow window(VideoMode(1600, 900), "Titre de la fenêtre");
	Event event;
	RectangleShape fondEcran;
	View viewGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	viewGame.zoom(0.30);
	viewGame.move(1800, -100);



	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.setView(viewGame);
		window.draw(getBG());
		window.display();
	}
}

const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}

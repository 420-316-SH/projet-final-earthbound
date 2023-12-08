#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "entite.h"
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
}

void Game::play()
{
}

const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}

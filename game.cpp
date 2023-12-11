#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "vecteur.hpp"
#include "status.h"
#include "move.h"
#include "entite.h"
#include "joueur.h"
#include "game.h"

using namespace sf;
Game::Game()
{

}
Game::~Game()
{
}
void Game::init(int posX, int posY, int w, int h, const char* nomSprite)
{
	_fondEcranPlay.setPosition(posX, posY);
	_fondEcranPlay.setSize(Vector2f(w, h));
	if (!_textureBgMap.loadFromFile("img/bgMap.png"))
	{
		exit(1);
	}
	_fondEcranPlay.setTexture(&_textureBgMap);
	vecteur<Move> moveNess;
	sf::IntRect rectSpriteNess(35, 14, 16, 24);
 	_ness.setJoueur(true, 100, 2, 2, 0, 0, 1, 1, 0, 10, 10, moveNess, 2550, 350, 16, 24, rectSpriteNess, "img/ness.png");

}

void Game::play()
{
	init(0, 0, 3000, 3328, "img/bgMap.png");
	RenderWindow window(VideoMode(1600, 900), "Titre de la fenêtre");
	Event event;
	RectangleShape fondEcran;
	View viewGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	viewGame.zoom(0.3);
	viewGame.move(1800, -100);

	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);


	////////////////////////////////////////////////////////////////////////
	//TEST MOVE ANIMATION

	//Clock pour limiter les fps surtout pour la gestion des animations
	Clock clock;
	Time time;

	RectangleShape animationTest;
	IntRect animationFrame(1 , 226, 256, 224);
	animationTest.setSize(Vector2f(256, 224));
	Texture textureAnimation;

	if (!textureAnimation.loadFromFile("img/testAnimation.png"))
	{
		exit(1);
	}

	animationTest.setTexture(&textureAnimation);
	animationTest.setTextureRect(animationFrame);
	int cptLeft=0;
	int cptTop=0;
	viewGame.zoom(5);
	viewGame.move(-1800,100);
	
	//////////////////////////////////////////////////////////////////



	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		/////////////////////////////////////////////////////////////////////
		//ANIMATION
		time = clock.getElapsedTime();
		if (time.asMilliseconds() >= 100.0f)
		{
		////////////////////////////////////////////////////////////////////	
			window.clear();
			window.setView(viewGame);
			window.draw(getBG());
			window.draw(_ness.getShape());
			//////////////////////////////////////////////////////////////
			//TEST ANIMATION

			window.draw(animationTest);
			if (cptLeft < 4 )
			{
				cptLeft++;
				animationFrame.left += 257;
			}
			else if (cptTop < 17)
			{
				cptTop++;
				cptLeft = 0;
				animationFrame.left = 1;
				animationFrame.top += 225;
				                    
			}
			else
			{
				cptLeft = 0;
				cptTop = 0;
				animationFrame.left = 1;
				animationFrame.top = 1;
			}
			cout << cptLeft << " " << cptTop;
			animationTest.setTextureRect(animationFrame);
			clock.restart();
			/////////////////////////////////////////////////////////////
			window.display();
		}
	}
}

const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}

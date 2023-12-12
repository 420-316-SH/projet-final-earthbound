#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "list.hpp"
#include "vecteur.hpp"
#include "item.h"
#include "status.h"
#include "move.h"
#include "entite.h"
#include "monstre.h"
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
	sf::IntRect rectSpriteNess(0, 14, 16, 24);
 	_ness.setJoueur(true, 100, 2, 2, 0, 0, 1, 1, 0, 10, 10, moveNess, 2550, 350, 16, 24, rectSpriteNess, "img/ness.png");
	_monstre.setJoueur(true, 100, 2, 2, 0, 0, 1, 1, 0, 10, 10, moveNess, 2500, 350, 16, 24, rectSpriteNess, "img/ness.png");
}

void Game::play()
{
	float lastX = 0;
	float lastY = 0;
	int dir = 0;
	int dirX = 0;
	int dirY = 0;
	float temp = 0;
	int animationCpt = 0;
	int cpt = 0;

	init(0, 0, 3000, 3328, "img/bgMap.png");
	RenderWindow window(VideoMode(1600, 900), "Titre de la fenêtre");
	Event event;
	RectangleShape fondEcran;
	View viewGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	viewGame.zoom(0.3);
	viewGame.move(1800, -100);

	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				switch (event.key.code) {
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::S:

					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						dir = 5;//bas gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::D))
					{
						dir = 6;//bas droite
					}
					else
					{
						dir = 1;//bas
					}
					break;
				case Keyboard::W:
					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						dir = 7;//haut gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::D))
					{
						dir = 8;//haut droite
					}
					else
					{
						dir = 2;//Haut
					}
					break;
				case Keyboard::A:
					if (Keyboard::isKeyPressed(Keyboard::S))
					{
						dir = 9;//Gauche bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::W))
					{
						dir = 10;//Gauche haut
					}
					else
					{
						dir = 3;//gauche
					}

					break;
				case Keyboard::D:
					if (Keyboard::isKeyPressed(Keyboard::S))
					{
						dir = 11;//Droite bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::W))
					{
						dir = 12;//Droite haut
					}
					else
					{
						dir = 4;//Droite
					}
					break;
				default:
					dir = 0;
					break;
				}

				//std::cout << dir << std::endl;
			}
			else if (event.type == Event::KeyReleased)//Pour régler les diagonales qui continue même si on à Released une touche
			{
				switch (event.key.code)
				{
				case Keyboard::S:
					//std::cout << "Released" << event.type;
					switch (dir)
					{
					case 1:
						dir = 0;
						break;
					case 5:
						dir = 3;
						break;
					case 6:
						dir = 4;
						break;
					case 9:
						dir = 3;
						break;
					case 11:
						dir = 4;
					default:
						break;
					}
					break;
				case Keyboard::W:
					switch (dir)
					{
					case 2:
						dir = 0;
						break;
					case 7:
						dir = 3;
						break;
					case 8:
						dir = 4;
						break;
					case 10:
						dir = 3;
						break;
					case 12:
						dir = 4;
						break;
					default:
						break;
					}
					break;
				case Keyboard::A:
					switch (dir)
					{
					case 3:
						dir = 0;
						break;
					case 5:
						dir = 1;
						break;
					case 7:
						dir = 2;
						break;
					case 9:
						dir = 1;
						break;
					case 10:
						dir = 2;
						break;
					default:
						break;
					}
					break;
				case Keyboard::D:
					switch (dir)
					{
					case 4:
						dir = 0;
						break;
					case 6:
						dir = 1;
						break;
					case 8:
						dir = 2;
						break;
					case 11:
						dir = 1;
						break;
					case 12:
						dir = 2;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
			else if (event.type == Event::JoystickMoved)
			{
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					lastX = Joystick::getAxisPosition(0, sf::Joystick::X) / 25;
					std::cout << "X: " << Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
					if (lastX < 0)
					{
						dirX = 3;
					}
					else if (lastX > 0)
					{
						dirX = 4;
					}
				}
				if (event.joystickMove.axis == sf::Joystick::Y)
				{
					lastY = event.joystickMove.position / 25;
					std::cout << "Y: " << Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
					if (lastY < 0)
					{
						dirY = 2;
					}
					else if (lastY > 0)
					{
						dirY = 1;
					}
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// À METTRE EN FONCTIOM SI ON A LE TEMPS
				// Doit déterminer la valeur la plus importante pour choisir quelle sprite afficher pour le bonhomme
				// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//comparer lastX et lastY
				if (lastX < 0 && lastY > 0)
				{
					//conversion
					temp = lastX * -1;
					if (temp >= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastX > 0 && lastY < 0)
				{
					//conversion
					temp = lastY * -1;
					if (temp >= lastX)
					{
						dir = dirY;
					}
					else
					{
						dir = dirX;
					}
				}
				else if (lastY < 0 && lastX < 0)
				{
					if (lastX <= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastY > 0 && lastX > 0)
				{
					if (lastX > lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				//deadZone pas de movement
				if (lastX < 0.2 && lastX > -0.2 && lastY < 0.2 && lastY > -0.2)
				{
					dir = 0;
					lastX = 0;
					lastY = 0;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		window.clear();
		window.setView(viewGame);
		window.draw(getBG());
		window.draw(_ness.getShape());
		window.draw(_monstre.getShape());
		_ness.move(dir, lastX, lastY, animationCpt);
		cpt = _monstre.moveMonstre(cpt);
		window.display();
	}
}

const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}

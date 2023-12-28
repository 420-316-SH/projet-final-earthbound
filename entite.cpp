#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <string>
#include "Entite.h"

Entite::Entite()
{
	_nom = "";
}

Entite::Entite(std::string nom, sf::RectangleShape& shape, sf::Texture& texture, sf::IntRect& rectSprite, sf::RectangleShape& hitbox)
{
	_nom = nom;
	shape;	// Pour la position et la forme
	texture;		// Pour les sprite
	rectSprite;	// Pour les animations
	hitbox; // Pour les collisions
}

Entite::~Entite()
{
	_nom = "";
}

void Entite::init(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite)
{
	_shape.setPosition(posX, posY);
	_shape.setSize(sf::Vector2f(w, h));
	if (!_texture.loadFromFile(nomSprite))
	{
		exit(1);
	}
	_shape.setTexture(&_texture);
	_rectSprite = rectSprite;
	_shape.setTextureRect(rectSprite);
	_hitbox.setPosition(posX + 6, posY + 6);
	_hitbox.setSize(sf::Vector2f(w - 12, h - 12));
	_hitbox.setFillColor(sf::Color::Black);
}

const std::string Entite::getNom() const
{
	return _nom;
}

const sf::RectangleShape Entite::getShape() const
{
	return _shape;
}

const sf::Vector2f& Entite::getPosition() const
{
	return _shape.getPosition();
}

const sf::Vector2f& Entite::getHitboxPosition() const
{
	return _hitbox.getPosition();
}

const sf::RectangleShape Entite::getHitbox() const
{
	return _hitbox;
}

void Entite::setNom(std::string nom)
{
	_nom = nom;
}

void Entite::setPosition(int posX, int posY)
{
	_shape.setPosition(posX, posY);
}

void Entite::setPosition(const sf::Vector2f& pos)
{
	_shape.setPosition(pos);
}

void Entite::setHitboxPosition(int posX, int posY)
{
	_hitbox.setPosition(posX, posY);
}

void Entite::setSize(int w, int h)
{
	_shape.setSize(sf::Vector2f(w, h));
}

sf::View Entite::move(int& dir, float x, float y, int& animationCpt, sf::View viewGame)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (x == 0) && (y == 0))
	{
		if (dir > 0)
		{
			animationCpt++;
			if (animationCpt >= 400)
			{
				_rectSprite.left += 16;
				animationCpt = 0;
			}
			if (_rectSprite.left >= 64)
			{
				_rectSprite.left = 0;
			}
		}
		switch (dir)
		{
		case 1://down
			_rectSprite.top = 0;
			_shape.move(0, 0.025);
			_hitbox.move(0, 0.025);
			//viewGame.move(0, 0.025);
			break;

		case 2://up
			_rectSprite.top = 24;
			_shape.move(0, -0.025);
			_hitbox.move(0, -0.025);
			//viewGame.move(0, -0.025);
			break;

		case 3://left
			_rectSprite.top = 72;
			_shape.move(-0.025, 0);
			_hitbox.move(-0.025, 0);
			//viewGame.move(-0.025, 0);
			break;

		case 4://right
			_rectSprite.top = 48;
			_shape.move(0.025, 0);
			_hitbox.move(0.025, 0);
			//viewGame.move(0.025, 0);
			break;

		case 5://down left
			_rectSprite.top = 0;
			_shape.move(-0.025, 0.025);
			_hitbox.move(-0.025, 0.025);
			//viewGame.move(-0.025, 0.025);
			break;

		case 6://down right
			_rectSprite.top = 0;
			_shape.move(0.025, 0.025);
			_hitbox.move(0.025, 0.025);
			//viewGame.move(0.025, 0.025);
			break;

		case 7://up left
			_rectSprite.top = 24;
			_shape.move(-0.025, -0.025);
			_hitbox.move(-0.025, -0.025);
			//viewGame.move(-0.025, -0.025);
			break;

		case 8://up right
			_rectSprite.top = 24;
			_shape.move(0.025, -0.025);
			_hitbox.move(0.025, -0.025);
			//viewGame.move(0.025, -0.025);
			break;

		case 9://left down
			_rectSprite.top = 72;
			_shape.move(-0.025, 0.025);
			_hitbox.move(-0.025, 0.025);
			//viewGame.move(-0.025, 0.025);
			break;

		case 10://left up
			_rectSprite.top = 72;
			_shape.move(-0.025, -0.025);
			_hitbox.move(-0.025, -0.025);
			//viewGame.move(-0.025, -0.025);
			break;

		case 11://right down
			_rectSprite.top = 48;
			_shape.move(0.025, 0.025);
			_hitbox.move(0.025, 0.025);
			//viewGame.move(0.025, 0.025);
			break;

		case 12://right up
			_rectSprite.top = 48;
			_shape.move(0.025, -0.025);
			_hitbox.move(0.025, -0.025);
			//viewGame.move(0.025, -0.025);
			break;

		default:
			animationCpt = 0;
			break;
		}
		_shape.setTextureRect(_rectSprite);
	}
	else if (x != 0 || y != 0)//joystick
	{
		if (dir != 0)
		{
			animationCpt++;
			switch (dir)
			{
			case 1:
				_rectSprite.top = 0;
				break;

			case 2:
				_rectSprite.top = 24;
				break;

			case 3:
				_rectSprite.top = 72;
				break;

			case 4:
				_rectSprite.top = 48;
				break;
			default:
				break;
			}
		}
		else
			animationCpt = 0;
		if (animationCpt == 400)
		{
			_rectSprite.left += 16;
			if (_rectSprite.left >= 64)
			{
				_rectSprite.left = 0;
			}
			animationCpt = 0;
		}
		_shape.setTextureRect(_rectSprite);
		_shape.move(x/150, y/150);
		_hitbox.setPosition(_shape.getPosition().x + 6, _shape.getPosition().y + 6);
		//viewGame.move(x/150, y/150);

	}
	//viewGame.setCenter(_shape.getPosition());
	return viewGame;
}

int Entite::moveMonstre(int cpt)
{

	if (cpt >= 0 && cpt < 2500)
	{
		_shape.move(0.030, 0);
		_hitbox.move(0.030, 0);
		cpt++;
	}
	else if (cpt >= 2500 && cpt < 5000)
	{
		_shape.move(0, 0.030);
		_hitbox.move(0, 0.030);
		cpt++;
	}
	else if (cpt >= 5000 && cpt < 7500)
	{
		_shape.move(-0.030, 0);
		_hitbox.move(-0.030, 0);
		cpt++;
	}
	else
	{
		_shape.move(0, -0.030);
		_hitbox.move(0, -0.030);
		cpt++;
	}
	if (cpt == 10000) 
	{
		cpt = 0;
	}
	return cpt;
}

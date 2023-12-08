#include <SFML/Graphics.hpp>
#include <cassert>
#include "Entite.h"

Entite::Entite()
{
	_nom ="";
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

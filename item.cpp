#include <SFML/Graphics.hpp>
#include <string>
#include "item.h"


Item::Item()
{
	_id = 0;
	_nom = "";
	_force = 0;
	_statistique = "";
	_consomable = false;
}

Item::Item(int id, std::string nom, int force, std::string statistique, bool consomable)
{
	_id = id;
	setNom(nom);
	setForce(force);
	setStat(statistique);
	setConso(consomable);
}

Item::~Item()
{
	_nom = "";
	_force = 0;
	_statistique = "";
	_consomable = false;
}

const int Item::getId() const
{
	return _id;
}

const std::string Item::getNom() const
{
	return _nom;
}

const int Item::getForce() const
{
	return _force;
}

const std::string Item::getStat() const
{
	return _statistique;
}

const bool Item::getConso() const
{
	return _consomable;
}

void Item::setNom(std::string nom)
{
	_nom = nom;
}

void Item::setForce(int force)
{
	_force = force;
}

void Item::setStat(std::string statistique)
{
	_statistique = statistique;
}

void Item::setConso(bool consomable)
{
	_consomable = consomable;
}

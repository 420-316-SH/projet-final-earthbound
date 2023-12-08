#include <SFML/Graphics.hpp>
#include <cassert>
#include "status.h"

status::status()
{
	_nom = "";
	_duree = 0;					
	_selfHeal = 0;			

	_alteredStat = "";
	_alterValue = 0;
}

status::~status()
{
	_nom = "";
	_duree = 0;
	_selfHeal = 0;

	_alteredStat = "";
	_alterValue = 0;
}

void status::init(std::string nom, int duree, float selfHeal, std::string alteredStat, int alterValue)
{
	_nom = nom;
	_duree = duree;
	_selfHeal = selfHeal;

	_alteredStat = alteredStat;
	_alterValue = alterValue;
}

std::string status::getNom()
{
	return _nom;
}

int status::getDuree()
{
	return _duree;
}

float status::getSelfHeal()
{
	return _selfHeal;
}

std::string status::getAlteredStat()
{
	return _alteredStat;
}

int status::getAlterValue()
{
	return _alterValue;
}

void status::setNom(std::string nom)
{
	_nom = nom;
}

void status::setDuree(int duree)
{
	_duree = duree;
}

void status::setSelfHeal(float selfHeal)
{
	_selfHeal = selfHeal;
}

void status::setAlteredStat(std::string alteredStat)
{
	_alteredStat = alteredStat;
}

void status::setAlterValue(int alterValue)
{
	_alterValue = alterValue;
}
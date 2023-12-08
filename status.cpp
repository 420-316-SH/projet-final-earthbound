#include <SFML/Graphics.hpp>
#include <cassert>
#include "Status.h"

Status::Status()
{
	_nom = "";
	_duree = 0;					
	_selfHeal = 0;			

	_alteredStat = "";
	_alterValue = 0;
}

Status::~Status()
{
	_nom = "";
	_duree = 0;
	_selfHeal = 0;

	_alteredStat = "";
	_alterValue = 0;
}

void Status::init(std::string nom, int duree, float selfHeal, std::string alteredStat, int alterValue)
{
	_nom = nom;
	_duree = duree;
	_selfHeal = selfHeal;

	_alteredStat = alteredStat;
	_alterValue = alterValue;
}

std::string Status::getNom()
{
	return _nom;
}

int Status::getDuree()
{
	return _duree;
}

float Status::getSelfHeal()
{
	return _selfHeal;
}

std::string Status::getAlteredStat()
{
	return _alteredStat;
}

int Status::getAlterValue()
{
	return _alterValue;
}

void Status::setNom(std::string nom)
{
	_nom = nom;
}

void Status::setDuree(int duree)
{
	_duree = duree;
}

void Status::setSelfHeal(float selfHeal)
{
	_selfHeal = selfHeal;
}

void Status::setAlteredStat(std::string alteredStat)
{
	_alteredStat = alteredStat;
}

void Status::setAlterValue(int alterValue)
{
	_alterValue = alterValue;
}
#include "vecteur.hpp"
#include "status.h"
#include "move.h"

Move::Move()
{
	_nom = "";
	_degats = 0;
	_ppCost = 0;
	//_statusInflict = Status();
}

Move::Move(std::string nom, int degats, int ppCost, std::string statAffect)
{
	_nom = nom;
	_degats = degats;
	_ppCost = ppCost;
	_statAffect = statAffect;
}

Move::~Move()
{
	_nom = "";
	_degats = 0;
	_ppCost = 0;
	//_statusInflict = Status();
}

const std::string Move::getNom() const
{
	return _nom;
}

const int Move::getDegats() const
{
	return _degats;
}

const int Move::getPpCost() const
{
	return _ppCost;
}

const std::string Move::getStatAffect() const
{
	return _statAffect;
}

void Move::setNom(std::string nom) 
{
	_nom = nom;
}

void Move::setDegats(int degats)
{
	_degats = degats;
}

void Move::setPpCost(int ppCost)
{
	_ppCost = ppCost;
}

void Move::setStatAffect(std::string statAffect)
{
	_statAffect = statAffect;
}
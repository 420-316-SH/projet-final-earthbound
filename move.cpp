#include "vecteur.hpp"
#include "status.h"
#include "move.h"

Move::Move()
{
	_nom = "";
	_degats = 0;
	_ppCost = 0;
	_statusInflict = Status();
}

Move::~Move()
{
	_nom = "";
	_degats = 0;
	_ppCost = 0;
	_statusInflict = Status();
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

const Status Move::getStatusInflict() const
{
	return _statusInflict;
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

void Move::setStatusInflict(Status statusInflict)
{
	_statusInflict = statusInflict;
}
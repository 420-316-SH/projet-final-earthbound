#include "move.h"
#include "vecteur.hpp"
#include "status.h"

const string Move::getNom() const
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

void Move::setNom(string nom) 
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
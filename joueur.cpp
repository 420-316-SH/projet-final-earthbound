#include "vecteur.hpp"
#include "status.h"
//#include "item.h"
#include "move.h"
#include "list.hpp"
#include "joueur.h"

const bool Joueur::getVivant() const
{
	return _vivant;
}

const Status Joueur::getStatus() const
{
	return _status;
}

/*const List<Item> Joueur::getInventaire() const
{
	return _inventaire;
}*/

const int Joueur::getHp() const
{
	return _hp;
}

const int Joueur::getIntel() const
{
	return _intel;
}

const int Joueur::getForce() const
{
	return _force;
}

const int Joueur::getDef() const
{
	return _def;
}

const float Joueur::getCrit() const
{
	return _crit;
}

const int Joueur::getSpeed() const
{
	return _speed;
}

const int Joueur::getLvl() const
{
	return _lvl;
}

const int Joueur::getExp() const
{
	return _exp;
}

const int Joueur::getPp() const
{
	return _pp;
}

const int Joueur::getNextLvl() const
{
	return _nextLvl;
}

const vecteur<Move> Joueur::getMoveset() const
{
	return _moveset;
}

void Joueur::setVivant(bool vivant)
{
	_vivant = vivant;
}

void Joueur::setStatus(Status status)
{
	_status = status;
}

/*void Joueur::addItem(Item newItem)
{
	_inventaire.end();
	_inventaire.insert(newItem);
}*/

/*void Joueur::removeItem(Item usedItem)
{
	assert(!_inventaire.empty());

	_inventaire.erase(_inventaire(usedItem));
}*/

void Joueur::setHp(int hp)
{
	_hp = hp;
}

void Joueur::setIntel(int intel)
{
	_intel = intel;
}

void Joueur::setForce(int force)
{
	_force = force;
}

void Joueur::setDef(int def)
{
	_def = def;
}

void Joueur::setCrit(float crit)
{
	_crit = crit;
}

void Joueur::setSpeed(int speed)
{
	_speed = speed;
}

void Joueur::setLvl(int lvl)
{
	_lvl = lvl;
}

void Joueur::setExp(int exp)
{
	_exp = exp;
}

void Joueur::setPp(int pp)
{
	_pp = pp;
}

void Joueur::setNextLvl(int nextLvl)
{
	_nextLvl = nextLvl;
}

void Joueur::addMove(Move move)
{
	_moveset.push_back(move);
}

Joueur::Joueur()
{
	_vivant = true;
	_status = Status();
	//_inventaire = List<Item>();
	_hp = 0;
	_intel = 0;
	_force = 0;
	_def = 0;
	_crit = 0;
	_speed = 0;
	_lvl = 0;
	_exp = 0;
	_pp = 0;
	_nextLvl = 0;
	_moveset = vecteur<Move>();
}

Joueur::~Joueur()
{
	_vivant = true;
	_status = Status();
	//_inventaire = List<Item>();
	_hp = 0;
	_intel = 0;
	_force = 0;
	_def = 0;
	_crit = 0;
	_speed = 0;
	_lvl = 0;
	_exp = 0;
	_pp = 0;
	_nextLvl = 0;
	_moveset = vecteur<Move>();
}

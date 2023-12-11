#include <SFML/Graphics.hpp>
#include "list.hpp"
#include "vecteur.hpp"
#include "status.h"
#include "move.h"
#include "entite.h"
#include "item.h"
#include "joueur.h"


Joueur::Joueur()
{
	_vivant = false;
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
	//_moveset = vecteur<Move>(); Pas besoin parceque le constructeur de la classe vecteur fera un vecteur vide
}

Joueur::~Joueur()
{
	_vivant = true;
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
	//_moveset = vecteur<Move>(); Pris en charge pas le desctructeur de la classe vecteur
}

const bool Joueur::getVivant() const
{
	return _vivant;
}

const Status Joueur::getStatus() const
{
	return _status;
}

/*const List<int> Joueur::getInventaire() const
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

void Joueur::setJoueur(bool vivant, int hp, int intel, int force, int def, float crit, int speed, int lvl, int exp, int pp, int nextLvl, vecteur<Move>& moveset, int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite)
{
	setVivant(vivant);
	setHp(hp);
	setIntel(intel);
	setForce(force);
	setDef(def);
	setCrit(crit);
	setSpeed(speed);
	setLvl(lvl);
	setExp(exp);
	setPp(pp);
	setNextLvl(nextLvl);
	init(posX,posY,w,h,rectSprite,nomSprite);
	_moveset = moveset;
	
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
	_inventaire.insert(_inventaire.end(), newItem.getId());
}*/

/*void Joueur::removeItem(Item usedItem)
{
	assert(!_inventaire.empty());

	_inventaire.erase(_inventaire(usedItem.getId()));
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


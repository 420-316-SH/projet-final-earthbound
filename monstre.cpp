#include <SFML/Graphics.hpp> //Est-ce necessaire dans mes pages/dans toutes les pages?
#include <cassert>
#include "entite.h"
#include "status.h"
#include "move.h"
#include "vecteur.hpp"
#include "monstre.h"

Monstre::Monstre()
{
	_vivant = false;

	_hp = _intel = _force = _def = _speed = _lvl = _expGagne = _crit = 0;
}

Monstre::~Monstre()
{
	_vivant = false;

	_hp = _intel = _force = _def = _speed = _lvl = _expGagne = _crit = 0;
}

bool Monstre::getVivant() const
{
	return _vivant;
}

Status Monstre::getStatus() const
{
	return _status;
}

int Monstre::getHp() const
{
	return _hp;
}

int Monstre::getIntel() const
{
	return _intel;
}

int Monstre::getForce() const
{
	return _force;
}

int Monstre::getDef() const
{
	return _def;
}

int Monstre::getSpeed() const
{
	return _speed;
}

int Monstre::getLvl() const
{
	return _lvl;
}

int Monstre::getExpGagne() const
{
	return _expGagne;
}

float Monstre::getCrit() const
{
	return _crit;
}

std::string Monstre::getDialogue() const
{
	return _dialogue;
}

vecteur<Move> Monstre::getMoveSet() const
{
	return _moveSet;
}

void Monstre::setVivant(bool vivant)
{
	_vivant = vivant;
}

void Monstre::setStatus(std::string nom, int duree, float selfHeal, std::string alteredStat, int alterValue)
{
	_status.init(nom, duree, selfHeal, alteredStat, alterValue); //il faudra un opérateur = pour la classe status; Quelle propriété du statut on souhaite affiché? on aura besoin d'un opérateur << dans statut et d'une propriété print
}

void Monstre::setHp(int hp)
{
	_hp = hp;
}

void Monstre::setIntel(int intel)
{
	_intel = intel;
}

void Monstre::setForce(int force)
{
	_force = force;
}

void Monstre::setDef(int def)
{
	_def = def;
}

void Monstre::setSpeed(int speed)
{
	_speed = speed;
}

void Monstre::setLvl(int lvl)
{
	_lvl = lvl;
}

void Monstre::setExpGagne(int expGagne)
{
	_expGagne = expGagne;
}

void Monstre::setCrit(float crit)
{
	_crit = crit;
}

void Monstre::setDialogue(std::string dialogue)
{
	_dialogue = dialogue;
}

void Monstre::setMoveSet(vecteur<Move> moveSet)
{
	_moveSet = moveSet; //il faudra un opérateur = pour la classe status; Quelle propriété du statut on souhaite affiché? on aura besoin d'un opérateur << dans statut et d'une propriété print
}

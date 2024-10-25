#include <SFML/Graphics.hpp> //Est-ce necessaire dans mes pages/dans toutes les pages?
#include "vecteur.hpp"
#include "entite.h"
#include "item.h"
#include "status.h"
#include "move.h"
#include "monstre.h"

Monstre::Monstre()
{
	_vivant = false;

	_hp = _intel = _force = _def = _speed = _lvl = _expGagne = _crit = 0;
}

Monstre::~Monstre()
{
	_vivant = false;
	_shape.setSize(sf::Vector2f(0, 0));
	_shape.setPosition(sf::Vector2f(-1000, -1000));

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

Item Monstre::getButtin() const
{
	return _buttin;
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

void Monstre::setMonstre(bool vivant, int hp, int intel, int force, int def, float crit, int speed, int lvl, int expGagne, vecteur<Move>& moveset, int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite)
{
	setVivant(vivant);
	setHp(hp);
	setIntel(intel);
	setForce(force);
	setDef(def);
	setCrit(crit);
	setSpeed(speed);
	setLvl(lvl);
	setExpGagne(expGagne);
	init(posX, posY, w, h, rectSprite, nomSprite);
	_moveSet = moveset;
}

void Monstre::setVivant(bool vivant)
{
	_vivant = vivant;
}

void Monstre::setStatus(std::string nom, int duree, float selfHeal, std::string alteredStat, int alterValue)
{
	_status.init(nom, duree, selfHeal, alteredStat, alterValue); //il faudra un op�rateur = pour la classe status; Quelle propri�t� du statut on souhaite affich�? on aura besoin d'un op�rateur << dans statut et d'une propri�t� print
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
	_moveSet = moveSet; //il faudra un op�rateur = pour la classe status; Quelle propri�t� du statut on souhaite affich�? on aura besoin d'un op�rateur << dans statut et d'une propri�t� print
}

void Monstre::setButtin(Item buttin)
{
	_buttin = buttin;
}

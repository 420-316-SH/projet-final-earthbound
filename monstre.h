#pragma once
class Monstre : public Entite
{
private:
	bool _vivant;

	Status _status;

	int _hp;
	int _intel; //à quoi sert cette propriété?
	int _force;
	int _def;
	int _speed;
	int _lvl;
	int _expGagne;
	Item _buttin;
	float _crit;

	std::string _dialogue;

	vecteur<Move> _moveSet;

public:
	Monstre();
	~Monstre();

	bool getVivant()const;
	Status getStatus()const;
	int getHp()const;
	int getIntel()const;
	int getForce()const;
	int getDef()const;
	int getSpeed()const;
	int getLvl()const;
	int getExpGagne()const;
	Item getButtin()const;
	float getCrit()const;
	std::string getDialogue()const;
	vecteur<Move> getMoveSet()const;

	void setMonstre(bool vivant, int hp, int intel, int force, int def, float crit, int speed, int lvl, int expGagne, vecteur<Move>& moveset, int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite);
	void setVivant(bool vivant);
	void setStatus(std::string nom, int duree, float selfHeal, std::string alteredStat, int alterValue); //À revoir
	void setHp(int hp);
	void setIntel(int intel);
	void setForce(int force);
	void setDef(int def);
	void setSpeed(int speed);
	void setLvl(int lvl);
	void setExpGagne(int expGagne);
	void setCrit(float crit);
	void setDialogue(std::string dialogue);
	void setMoveSet(vecteur<Move> moveSet);
	void setButtin(Item buttin);
};
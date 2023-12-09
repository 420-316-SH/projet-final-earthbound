#pragma once
class Joueur
{
private :
	bool _vivant;
	Status _status;
	//List<Item> _inventaire;
	int _hp;
	int _intel;
	int _force;
	int _def;
	float _crit;
	int _speed;
	int _lvl;
	int _exp;
	int _pp;
	int _nextLvl;
	vecteur<Move> _moveset;


	

public:
	Joueur();
	~Joueur();

	const bool getVivant() const;
	const Status getStatus() const;
	//const List<Item> getInventaire() const;
	const int getHp() const;
	const int getIntel() const;
	const int getForce() const;
	const int getDef() const;
	const float getCrit() const;
	const int getSpeed() const;
	const int getLvl() const;
	const int getExp() const;
	const int getPp() const;
	const int getNextLvl() const;
	const vecteur<Move> getMoveset() const;

	void setJoueur(bool vivant, int hp, int intel, int force, int def, float crit, int speed, int lvl, int exp, int pp, int nextLvl, vecteur<Move> moveset);
	void setVivant(bool vivant);
	void setStatus(Status status);
	//void addItem(Item newItem);
	//void removeItem(Item usedItem);
	void setHp(int hp);
	void setIntel(int intel);
	void setForce(int force);
	void setDef(int def);
	void setCrit(float crit);
	void setSpeed(int speed);
	void setLvl(int lvl);
	void setExp(int Exp);
	void setPp(int pp);
	void setNextLvl(int nextLvl);
	void addMove(Move move);
};


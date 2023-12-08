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

		float _crit;

		std::string _dialogue;

		vecteur<Move> _moveSet;

		//Obj buttin

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
		float getCrit()const;
		std::string getDialogue()const;
		vecteur<Move> getMoveSet()const;

		void setVivant(bool vivant);
		void setStatus(Status status);
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
};


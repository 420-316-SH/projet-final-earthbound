#pragma once
class Move
{
private:
	std::string _nom;
	int _degats;
	int _ppCost;
	std::string _statAffect;

public:
	Move();
	Move(std::string nom, int degats, int ppCost, std::string stataffect);
	~Move();

	const std::string getNom() const;
	const int getDegats() const;
	const int getPpCost() const;
	const std::string getStatAffect() const;

	void setNom(std::string nom);
	void setDegats(int degats);
	void setPpCost(int ppCost);
	void setStatAffect(std::string statAffect);
};


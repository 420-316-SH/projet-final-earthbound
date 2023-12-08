#pragma once
class Move
{
private:
	std::string _nom;
	int _degats;
	int _ppCost;
	Status _statusInflict;

public:
	const std::string getNom() const;
	const int getDegats() const;
	const int getPpCost() const;
	const Status getStatusInflict() const;

	void setNom(std::string nom);
	void setDegats(int degats);
	void setPpCost(int ppCost);
	void setStatusInflict(Status statusInflict);
};


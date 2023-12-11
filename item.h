#pragma once
class Item
{
private:
	int _id;
	std::string _nom;
	int _force;
	std::string _statistique;
	bool _consomable;

public:
	Item();
	Item(int id, std::string nom, int force, std::string statistique, bool consomable);
	~Item();

	const int getId() const;
	const std::string getNom() const;
	const int getForce() const;
	const std::string getStat() const;
	const bool getConso() const;

	void setNom(std::string nom);
	void setForce(int force);
	void setStat(std::string statistique);
	void setConso(bool consomable);
};


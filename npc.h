#pragma once
class Npc : public Entite
{
	private:
		std::string _dialogue; //Pourquoi ne pas mettre cette propriété dans la classe parent?
	public:
		Npc();
		~Npc();

		std::string getDialogue()const;
		void setDialogue(std::string dialogue);
};


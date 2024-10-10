#pragma once
class Npc : public Entite
{
	private:
		std::string _dialogue;
	public:
		Npc();
		~Npc();

		std::string getDialogue()const;
		void setDialogue(std::string dialogue);
};


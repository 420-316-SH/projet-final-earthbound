#include <SFML/Graphics.hpp>
#include <cassert>
#include "entite.h"
#include "npc.h"

Npc::Npc()
{
	_dialogue = "";
}

Npc::~Npc()
{
	_dialogue = "";
}

std::string Npc::getDialogue() const
{
	return _dialogue;
}

void Npc::setDialogue(std::string dialogue)
{
	_dialogue = dialogue;
}

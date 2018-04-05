#pragma once
#include "Interactuable.h"
class NPC :
	public Interactuable
{
public:
	NPC();
	~NPC();
	void activate();
};


class NPCcreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new NPC();
	}
};

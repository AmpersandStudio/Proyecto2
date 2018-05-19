#pragma once
#include "Cartel.h"
class Teleport :
	public Cartel
{
public:
	Teleport();
	~Teleport();

	void setLevelTeleport(int lvl) { changeLevel = lvl; };
	void update();
	void render();
	void activate();
protected:

	int changeLevel;
	virtual void selectAction();
	
};

class TeleportCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Teleport();
	}
};


#pragma once

#include "Interactuable.h"

class Door : public Interactuable
{
public:
	Door() {}
	virtual ~Door() {}

	inline int getId() const { return id_; }
	inline void setId(int id) { id_ = id; }

	virtual void render();
	virtual void activate();
	virtual string type() { return "Door"; }

private:	
	int id_; 
};

class DoorCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Door();
	}
};


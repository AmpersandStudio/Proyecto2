#pragma once

#include "Interactuable.h"

class Door : public Interactuable
{
public:
	Door() : active_(false) {}
	virtual ~Door() {}

	inline int getId() const { return id_; }
	inline void setId(int id) { id_ = id; }

	virtual void render();
	virtual void activate();
	virtual string type() { return "Door"; }

	inline bool isActive() const { return active_; }

private:	
	int id_; 
	bool active_;
};

class DoorCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Door();
	}
};


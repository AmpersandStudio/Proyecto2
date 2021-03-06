#pragma once
#include "PhysicsComponent.h"
#include "checkML.h"

class DiscretMovementIAComponent :
	public PhysicsComponent
{
private:
	int movement;
	int id_;
	bool first;
	bool altLap;
	bool flag;
public:
	DiscretMovementIAComponent(int id);
	~DiscretMovementIAComponent();
	virtual void update(GameObject * o);
	void horiz1(GameObject * o);
	void horiz2(GameObject * o);
	void vert1(GameObject * o);
	void alternate(GameObject * o);
};


#pragma once
#include "PhysicsComponent.h"

class DiscretMovementIAComponent :
	public PhysicsComponent
{
private:
	int movement;
	bool first;
	bool altLap;
	bool flag;
public:
	DiscretMovementIAComponent();
	~DiscretMovementIAComponent();
	virtual void update(GameObject * o);
	void horiz1(GameObject * o);
	void horiz2(GameObject * o);
	void vert1(GameObject * o);
	void alternate(GameObject * o);
};


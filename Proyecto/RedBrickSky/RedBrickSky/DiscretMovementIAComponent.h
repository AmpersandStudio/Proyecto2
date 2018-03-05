#pragma once
#include "PhysicsComponent.h"

class DiscretMovementIAComponent :
	public PhysicsComponent
{
public:
	DiscretMovementIAComponent();
	~DiscretMovementIAComponent();
	virtual void update(GameObject * o);
};


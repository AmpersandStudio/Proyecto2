#pragma once
#include "GameObject.h"

#include "checkML.h"

class PhysicsComponent
{
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update(GameObject* o) = 0;
};


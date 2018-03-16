#pragma once
#include "PhysicsComponent.h"
class MoveToThisPosComponent :
	public PhysicsComponent
{
private:
	Vector2D origPos;
	Vector2D enemPos;
	int dir;
	bool go_;
	bool back_;
public:
	MoveToThisPosComponent(Vector2D myPos, Vector2D hisPos);
	virtual ~MoveToThisPosComponent();
	virtual void update(GameObject* o);
};

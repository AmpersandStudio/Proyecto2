#pragma once
#include "PhysicsComponent.h"
#include "BattleCharacter.h"

#include "checkML.h"

class MoveToThisPosComponent :
	public PhysicsComponent
{
private:
	Vector2D origPos;
	Vector2D enemPos;
	int dir;
	bool go_;
	bool back_;
	bool isMoving_;
	double vel_;
	BattleCharacter* bc;

public:
	MoveToThisPosComponent() {};
	MoveToThisPosComponent(Vector2D myPos, Vector2D hisPos, double vel = 0.1);
	virtual ~MoveToThisPosComponent();
	virtual void update(GameObject* o);
};


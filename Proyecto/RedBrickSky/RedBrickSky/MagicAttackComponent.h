#pragma once
#include "PhysicsComponent.h"
#include "BattleCharacter.h"

#include "checkML.h"

class MagicAttackComponent : public PhysicsComponent
{
private:
	BattleCharacter* bc;
	bool isMoving = false;
	Vector2D position_;
	Vector2D origPosition_;
	int counter = 0;
	double maxX, minX;
	bool flag;

public:
	MagicAttackComponent() {}
	MagicAttackComponent(Vector2D position, double range);
	virtual ~MagicAttackComponent();
	virtual void update(GameObject* o);
};


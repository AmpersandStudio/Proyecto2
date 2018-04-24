#include "MagicAttackComponent.h"

#include "BattleState.h"

MagicAttackComponent::MagicAttackComponent(Vector2D position, double range) : position_(position), origPosition_(position)
{
	maxX = position.getX() + range;
	minX = position.getX() - range;
}

MagicAttackComponent::~MagicAttackComponent()
{
}

void MagicAttackComponent::update(GameObject* o) {
	double pixels = 0.1;
	
	if (counter % 2 == 0 && counter < 8) {
		isMoving = true;
		Vector2D p = o->getPosition();
		if (p.getX() < maxX) {
			double currX = p.getX() + pixels;
			p.setX(currX);
			o->setPosition(p);
		}
		else
			counter++;
	}
	else if (counter % 2 == 1 && counter < 8 ) {
		isMoving = true;
		Vector2D p = o->getPosition();
		if (p.getX() > minX) {
			double currX = p.getX() - pixels;
			p.setX(currX);
			o->setPosition(p);
		}
		else
			counter++;
	}

	else {
		bc = static_cast<BattleCharacter*>(o);
		bc->setTurn(false);
		isMoving = false;
	}
	
	if (!isMoving) {
		BattleState* bs = static_cast<BattleState*>(Game::Instance()->getStateMachine()->currentState());
		bs->setAttackAnim(false);
		o->setPosition(origPosition_);
	}
	else {
		BattleState* bs = static_cast<BattleState*>(Game::Instance()->getStateMachine()->currentState());
		bs->setAttackAnim(true);
	}
}

#include "DiscretMovementIAComponent.h"
#include "StateMachine.h"
#include "BattleState.h"

DiscretMovementIAComponent::DiscretMovementIAComponent()
{
}

DiscretMovementIAComponent::~DiscretMovementIAComponent()
{
}

void DiscretMovementIAComponent::update(GameObject * o) {
	int screenW = o->getGame()->getWinWidth();
	int screenH = o->getGame()->getWinHeight();
	Vector2D pos = o->getPosition();

	int rows = o->getGame()->getWinHeight() / o->getWidth();
	
	pos.setX((pos.getX()) + 1);
	if (pos.getX()*o->getWidth() < screenW)
		o->setPosition(pos);
	else if (pos.getX()*o->getWidth() >= screenW && pos.getY()*o->getHeight() < screenH)
	{
		pos.setX(0);
		pos.setY(pos.getY() + 1);
		o->setPosition(pos);
	}
	else {
		StateMachine* sm = o->getGame()->getStateMachine();
		sm->changeState(new BattleState(o->getGame()));
	}
}
#include "DiscretMovementIAComponent.h"

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
	pos.setX(pos.getX() + 1);
	if (pos.getX()*o->getWidth() < screenW)
		o->setPosition(pos);
}
#include "MoveToThisPosComponent.h"

MoveToThisPosComponent::MoveToThisPosComponent(Vector2D myPos, Vector2D hisPos) : enemPos(hisPos), origPos(myPos)
{
	//si el enem esta a la derecha de la pantalla dir = 1
	if (hisPos.getX() > myPos.getX())
		dir = 1;
	else
		dir = -1;

	go_ = true;
	back_ = false;
	isMoving_ = false;
}

MoveToThisPosComponent::~MoveToThisPosComponent()
{
}

void MoveToThisPosComponent::update(GameObject* o) {
	Vector2D currentPos = o->getPosition();
	double currentX = currentPos.getX();
	double objectiveX = enemPos.getX();
	double pixels = 0.3;
	if (dir == 1 && go_) {
		if (objectiveX > currentX) {
			currentX += pixels;
			
		}
		else {
			back_ = true;
			go_ = false;
		}
	}
	else if (dir == 1 && back_) {
		if (currentX > origPos.getX() + pixels)
			currentX -= pixels;
		else {
			back_ = false;
			o->setPosition(origPos);
			bc = static_cast<BattleCharacter*>(o);
			bc->setTurn(false);
		}
	}
	else if (dir == -1 && go_) {
		if (objectiveX < currentX) {
			currentX -= pixels;
		}
		else {
			back_ = true;
			go_ = false;
		}
	}
	else if (dir == -1 && back_) {
		if (currentX < origPos.getX() - pixels)
			currentX += pixels;
		else {
			back_ = false;
			o->setPosition(origPos);
			bc = static_cast<BattleCharacter*>(o);
			bc->setTurn(false);
		}
	}

	if (back_ || go_) {
		Vector2D v(currentX, o->getPosition().getY());
		o->setPosition(v);
	}
}
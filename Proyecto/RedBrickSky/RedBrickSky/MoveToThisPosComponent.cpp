#include "MoveToThisPosComponent.h"
#include "BattleState.h"

MoveToThisPosComponent::MoveToThisPosComponent(Vector2D myPos, Vector2D hisPos, double vel) : enemPos(hisPos), origPos(myPos), vel_(vel)
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
	double pixels = vel_;
	if (dir == 1 && go_) {
		if (objectiveX > currentX) {
			currentX += pixels;
			
		}
		else {
			back_ = true;
			go_ = false;
			TheSoundManager::Instance()->playSound(GameManager::Instance()->getAttackSound(), 0);
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
		BattleState* bs = static_cast<BattleState*>(Game::Instance()->getStateMachine()->currentState());
		bs->setAttackAnim(true);
	}

	else {
		BattleState* bs = static_cast<BattleState*>(Game::Instance()->getStateMachine()->currentState());
		bs->setAttackAnim(false);
	}
}
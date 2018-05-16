#include "DiscretMovementIAComponent.h"
#include "StateMachine.h"
#include "BattleState.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

DiscretMovementIAComponent::DiscretMovementIAComponent(int id) : id_(id)
{
	srand(time(NULL));
	movement = rand() % 4 + 1;
	first = true;
	altLap = false;
	flag = true;
}

DiscretMovementIAComponent::~DiscretMovementIAComponent()
{
}

void DiscretMovementIAComponent::update(GameObject * o) {
	if (movement == 1 && flag) {
		horiz1(o);
	}
	else if (movement == 2 && flag) {
		horiz2(o);
	}
	else if (movement == 3 && flag) {
		vert1(o);
	}
	else if (movement == 4 && flag) {
		alternate(o);
	}
	flag = !flag;
}

void DiscretMovementIAComponent::horiz1(GameObject * o) {
	int screenW = Game::Instance()->getWinWidth();
	int screenH = Game::Instance()->getWinHeight();
	Vector2D pos = o->getPosition();

	int rows = Game::Instance()->getWinHeight() / o->getHeight();
	if (first)
		first = false;
	else {
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
			Vector2D oriPos(0, 0);
			o->setPosition(oriPos);
			StateMachine* sm = Game::Instance()->getStateMachine();
			sm->changeState(new BattleState(id_));
		}
	}
}

void DiscretMovementIAComponent::horiz2(GameObject * o) {
	int screenW = Game::Instance()->getWinWidth();
	int screenH = Game::Instance()->getWinHeight();
	Vector2D pos = o->getPosition();

	int rows = Game::Instance()->getWinHeight() / o->getHeight();
	int cols = Game::Instance()->getWinWidth() / o->getWidth();

	pos.setX(pos.getX() - 1);

	if (pos.getX()*o->getWidth() < screenW && pos.getX()*o->getWidth() >= 0)
		o->setPosition(pos);

	else if (pos.getX() < 0 && first)
	{
		first = false;
		pos.setX((pos.getX()) + cols + 1);
		o->setPosition(pos);
	}

	else if (pos.getX()*o->getWidth() < 0 && pos.getY()*o->getHeight() < screenH)
	{
		pos.setX((pos.getX()) + cols);
		pos.setY(pos.getY() + 1);
		o->setPosition(pos);
	}

	else {
		Vector2D oriPos(-1, 0);
		o->setPosition(oriPos);
		StateMachine* sm = Game::Instance()->getStateMachine();
		sm->changeState(new BattleState(id_));
	}

}

void DiscretMovementIAComponent::vert1(GameObject * o) {
	int screenW = Game::Instance()->getWinWidth();
	int screenH = Game::Instance()->getWinHeight();
	Vector2D pos = o->getPosition();

	int rows = Game::Instance()->getWinHeight() / o->getHeight();
	int cols = Game::Instance()->getWinWidth() / o->getWidth();

	if (first)
		first = false;

	else {
		pos.setY((pos.getY()) + 1);
		if (pos.getY()*o->getHeight() < screenH)
			o->setPosition(pos);
		else if (pos.getY()*o->getHeight() >= screenH && pos.getX()*o->getWidth() < screenW)
		{
			pos.setY(0);
			pos.setX(pos.getX() + 1);
			o->setPosition(pos);
		}
		else {
			Vector2D oriPos(0, 0);
			o->setPosition(oriPos);
			StateMachine* sm = Game::Instance()->getStateMachine();
			sm->changeState(new BattleState(id_));
		}
	}
}

void DiscretMovementIAComponent::alternate(GameObject * o) {
	int screenW = Game::Instance()->getWinWidth();
	int screenH = Game::Instance()->getWinHeight();
	Vector2D pos = o->getPosition();

	int rows = Game::Instance()->getWinHeight() / o->getHeight();
	if (first)
		first = false;
	else {
		pos.setX((pos.getX()) + 2);
		if (pos.getX()*o->getWidth() < screenW && fmod(pos.getX(), 2) == 0 && !altLap)
			o->setPosition(pos);
		else if (pos.getX()*o->getWidth() >= screenW && pos.getY()*o->getHeight() < screenH && !altLap)
		{
			pos.setX(0);
			pos.setY(pos.getY() + 1);
			o->setPosition(pos);
		}

		else if (!altLap) {
			altLap = true;
			pos.setX(1);
			pos.setY(0);
			o->setPosition(pos);
		}

		if (pos.getX()*o->getWidth() < screenW && fmod(pos.getX(), 2) != 0 && altLap)
			o->setPosition(pos);
		else if (pos.getX()*o->getWidth() >= screenW && pos.getY()*o->getHeight() < screenH && altLap)
		{
			pos.setX(1);
			pos.setY(pos.getY() + 1);
			o->setPosition(pos);
		}

		else if (altLap) {
			Vector2D oriPos(0, 0);
			o->setPosition(oriPos);
			StateMachine* sm = Game::Instance()->getStateMachine();
			sm->changeState(new BattleState(id_));
		}
	}
}
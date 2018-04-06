#include "NPC.h"
#include "Level.h"
#include <time.h>
#include <stdlib.h> 

NPC::NPC()
{
	isInteracting_ = false;
	Vector2D v; v.set(3, 0);
	setVel(v);
	facingLeft_ = false;
	this->setColFrame(2);
	velocity_ = 3;
	stopped_ = false;

	srand(time(NULL)); // Semilla de aleatorio
}


NPC::~NPC()
{
}

void NPC::activate() {
	//isInteracting_ = true;
	std::cout << Msg_ << endl;
}

void NPC::update() {

	if(!isInteracting_ && !stopped_)
	move();

	if (movementCont_ > 40) {
		int rnd = rand() % 100 + 1;
		stopped_ = false;

		if (rnd < 60)
			collision();
		else {
			stopped_ = true;
			movementCont_ = 0;
		}
	}
}

void NPC::move() {
	Vector2D pos = getPosition();
	pos = pos + getVel();

	setPosition(pos);
	changeColliderPos(pos);
}

void NPC::collision()
{
	movementCont_ = 0;
	int rnd = rand() % 2;
	std::cout << "MovingNPC..." << endl;
	Vector2D d = getVel();

	if (rnd == 0) {

		if (d.getX() == 0)
		{
			int rnd2 = rand() % 2;
			if(rnd2 == 0)
				d.setX(velocity_);
			else 
				d.setX(-velocity_);
		}
			
		else
			d.setX(-velocity_);

		if (d.getX() > 0)
			facingLeft_ = false;
		else
			facingLeft_ = true;

		d.setY(0);
	}
	else if (rnd == 1) {

		if (d.getY() == 0) {
			int rnd2 = rand() % 2;

			if (rnd2 == 0)
				d.setY(velocity_);
			else
				d.setY(-velocity_);
		}

		else
			d.setY(-velocity_);

		//if (d.getY() > 0)
		//	facingLeft_ = false;
		//else
		//	facingLeft_ = true;
		d.setX(0);
	}

	setVel(d);
		
	
	if (facingLeft_)
		this->setColFrame(1);
	else
		this->setColFrame(2);
}
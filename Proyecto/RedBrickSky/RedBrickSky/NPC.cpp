#include "NPC.h"
#include "Level.h"
#include <time.h>
#include <stdlib.h> 


NPC::NPC()
{
	srand(time(NULL)); // Semilla de aleatorio
}

void NPC::load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed)
{
	position_ = position;
	width_ = width;
	height_ = height;
	textureId_ = textureId;
	numFrames_ = numFrames;
	callbackId_ = callbackID;
	animSpeed_ = animSpeed;
	oriPosX_ = position.getX();
	oriPosY_ = position.getY();

	isInteracting_ = false;

	this->setColFrame(2);
	velocity_ = 1;

	movementCont_ = rand() % 39;

	int rnd = rand() % 2;
	if (rnd == 0)
		velocity_ = -velocity_;

	int rnd2 = rand() % 2;
	if (rnd2 == 0)
		vel.set(velocity_, 0);
	else
		vel.set(0, velocity_);
	setVel(vel);
	stopped_ = false;
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
		collided_ = false;

		if (rnd < 70)
			collision();
		else {
			stopped_ = true;
			movementCont_ = 0;
		}
	}
	// refresh animation frame
	if (!stopped_)
		handleAnimation();
	else if(!collided_)
		handleStoppedAnimation();
}

void NPC::move() {
	Vector2D pos = getPosition();
	pos = pos + getVel();
	
	checkMapLimits(pos);
	//checkNPCLimits(pos);

	setPosition(pos);
	changeColliderPos(pos);
}

void NPC::checkMapLimits(Vector2D pos) {
	//Para asegurarnos de que no sale por la parte derecha ni inferior de la pantalla produciendo una excepción
	if (pos.getX() >= tileWidth_ - 30) {
		pos.setX(tileWidth_ - 35);
		invertVel();
	}

	else if (pos.getX() <= 30) {
		pos.setX(45);
		invertVel();
	}

	else if (pos.getY() >= tileHeight_ - 40) {
		pos.setY(tileHeight_ - 45);
		invertVel();
	}

	else if (pos.getY() <= 40) {
		pos.setY(45);
		invertVel();
	}
}

void NPC::checkNPCLimits(Vector2D pos) {
	//Para asegurarnos de que no sale de un rango de movimiento determinado
	if (pos.getX() >= oriPosX_ + 300) {
		collision();
	}

	else if (pos.getX() <= oriPosX_ - 300) {
		collision();
	}

	else if (pos.getY() >= oriPosY_ + 300) {
		collision();
	}

	else if (pos.getY() <= oriPosY_ - 300) {
		collision();
	}
}


void NPC::collision()
{
	movementCont_ = 0;
	int rnd = rand() % 2;
	vel = getVel();

	if (rnd == 0) {

		if (vel.getX() == 0)
		{
			int rnd2 = rand() % 2;
			if(rnd2 == 0)
				vel.setX(velocity_);
			else 
				vel.setX(-velocity_);
		}
			
		else
			vel.setX(-velocity_);

		vel.setY(0);
	}
	else if (rnd == 1) {

		if (vel.getY() == 0) {
			int rnd2 = rand() % 2;

			if (rnd2 == 0)
				vel.setY(velocity_);
			else
				vel.setY(-velocity_);
		}

		else
			vel.setY(-velocity_);
		vel.setX(0);
	}

	setVel(vel);
		
	
}

void NPC::handleAnimation()
{
	
		if (vel.getY() < 0)
		{
			rowFrame_ = 3;
		}
		else if (vel.getY() > 0)
		{
			rowFrame_ = 0;
		}
		else if (vel.getY() == 0)
		{
			rowFrame_ = (vel.getX() < 0) ? 1 : 2;
		}
		colFrame_ = int(((SDL_GetTicks() / (100)) % numFrames_));
	

}

void NPC::handleStoppedAnimation()
{
	if (vel.getY() < 0)
	{
		rowFrame_ = 3;
	}
	else if (vel.getY() > 0)
	{
		rowFrame_ = 0;
	}
	else if (vel.getY() == 0)
	{
		rowFrame_ = (vel.getX() < 0) ? 1 : 2;
	}

	colFrame_ = 1;
}
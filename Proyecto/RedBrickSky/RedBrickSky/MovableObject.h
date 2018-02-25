#pragma once
#include "GameComponent.h"
class MovableObject :
	public GameComponent
{

protected:
	Vector2D velocity_;


public:
	MovableObject(Game* game,Vector2D vel);
	~MovableObject();


	const Vector2D& getVelocity() const { return velocity_; };
	void setVelocity(const Vector2D &vel) { velocity_ = vel; velocity_.normalize(); };
};


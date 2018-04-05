#pragma once
#include "Interactuable.h"
class Cartel :
	public Interactuable
{
public:
	Cartel();
	~Cartel();
	void activate();

};

class CartelCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Cartel();
	}
};

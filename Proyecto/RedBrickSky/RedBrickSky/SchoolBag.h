#pragma once
#include "Interactuable.h"
#include "GameManager.h"

#include "checkML.h"
class SchoolBag :
	public Interactuable
{
public:
	SchoolBag();
	~SchoolBag();
	void activate();
	//Para establecer el mensaje si es necesario
	void setSweeties(int st) { Sweeties_ = st; };
private:
	int Sweeties_;
};

class BagCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new SchoolBag();
	}
};
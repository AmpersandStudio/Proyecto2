#pragma once
#include "Interactuable.h"
#include "GameManager.h"
class Key : public Interactuable
{

private:
	int keyID;

public:
	Key();
	~Key();

	virtual void activate();
	//Para establecer el mensaje si es necesario
	void setKeyID(int id) { keyID = id; };

};

class KeyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Key();
	}
};

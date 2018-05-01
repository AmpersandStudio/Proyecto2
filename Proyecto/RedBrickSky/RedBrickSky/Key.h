#pragma once
#include "Interactuable.h"
#include "GameManager.h"
class Key : public Interactuable
{

private:
	int keyID;
private:
	Uint32 timeStart_;
	Uint32 timeNameInterval_;
	Uint32 timeDisplayInterval_;
	Uint32 timeTitleInterval_;

	int col_;
	bool changed_;

public:
	Key();
	~Key();

	virtual void render();
	virtual void activate();
	virtual void update();
	//Para establecer el mensaje si es necesario
	void setKeyID(int id) { keyID = id; };
	void change();

};

class KeyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Key();
	}
};

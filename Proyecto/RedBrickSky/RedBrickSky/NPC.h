#pragma once
#include "Interactuable.h"

class Level;
class NPC :
	public Interactuable
{
public:
	NPC();
	~NPC();
	void update();
	void activate();
	void move();
	void setLevel(Level* l) { level_ = l; };
	void collision();
	void incrementMovCont() { movementCont_++; };
	void setMSG(std::string m) { Msg_ = m; };

private:
	bool isInteracting_;
	Level* level_;
	bool facingLeft_;
	int velocity_;
	int movementCont_;
	bool stopped_;
	std::string Msg_;
};


class NPCcreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new NPC();
	}
};

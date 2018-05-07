#pragma once

#include "Interactuable.h"
#include "Dialogue.h"

class Door : public Interactuable
{
public:
	Door() : active_(false),dialogueActive_(false),isInteracting_(false) {}
	virtual ~Door() {}

	inline int getID() const { return keyID_; }
	inline void setKeyID(int id) { keyID_ = id; }

	void setMSG(std::string m) { Msg_ = m; text = Dialogue(m); };

	virtual void update();
	virtual void render();
	virtual void activate();
	virtual string type() { return "Door"; }

	inline bool isActive() const { return active_; }

private:	
	int keyID_; 
	bool active_;

	std::string Msg_;
	Dialogue text;
	bool dialogueActive_;
	bool isInteracting_;
};

class DoorCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Door();
	}
};


#pragma once
#include "Interactuable.h"
#include "Game.h"
#include "Dialogue.h"

#include "checkML.h"
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
	void setMSG(std::string m) { Msg_ = m; text = Dialogue(m); };
	bool getState() { return stopped_; };
	void setCollided(bool b) { collided_ = b; stopped_ = true; };
	void handleAnimation();
	void handleStoppedAnimation();
	void invertVel() { velocity_ = -velocity_; };
	void render();



	void load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed);
	
	void checkMapLimits(Vector2D pos);
	void checkNPCLimits(Vector2D pos);

private:
	bool isInteracting_;
	Level* level_;
	int velocity_;
	int movementCont_;
	bool stopped_;
	std::string Msg_;
	Vector2D vel;
	bool collided_;
	double oriPosX_;
	double oriPosY_;



	Dialogue text;
	bool dialogueActive;
};


class NPCcreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new NPC();
	}
};

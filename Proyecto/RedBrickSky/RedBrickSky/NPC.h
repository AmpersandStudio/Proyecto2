#pragma once
#include "Interactuable.h"
#include "Game.h"
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
	bool getState() { return stopped_; };
	void handleAnimation();
	void invertVel() { velocity_ = -velocity_; };

	void setTileWidth(int t) { tileWidth_ = t; };
	void setTileHeight(int t) { tileHeight_ = t; };

	void load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed);
	

private:
	bool isInteracting_;
	Level* level_;
	int velocity_;
	int movementCont_;
	bool stopped_;
	std::string Msg_;
	Vector2D vel;

	int tileWidth_;
	int tileHeight_;
};


class NPCcreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new NPC();
	}
};

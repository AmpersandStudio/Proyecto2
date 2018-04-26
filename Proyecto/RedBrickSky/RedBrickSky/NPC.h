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
	void setLevel(Level* l) { level_ = l; };
	void incrementMovCont() { movementCont_++; };
	void setMSG(std::string m) { Msg_ = m; text = Dialogue(m); };
	bool getState() { return stopped_; };
	void setCollided(bool b) { collided_ = b; stopped_ = true; };
	void handleStoppedAnimation();
	void invertVel() { velocity_ = -velocity_; };
	void render();

	void setTileWidth(int t) { tileWidth_ = t; };
	void setTileHeight(int t) { tileHeight_ = t; };

	void load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed);

	bool getFighter() { return isFighter_; }
	void setFighter(bool set) { isFighter_ = set; }
	void isDefeated();

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

	int tileWidth_;
	int tileHeight_;

	Dialogue text;
	bool dialogueActive;

	bool isFighter_;

	int collisionCounter_;
};


class NPCcreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new NPC();
	}
};

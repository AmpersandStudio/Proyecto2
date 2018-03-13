#pragma once

#include "GameObject.h"
#include "GameObjectFactory.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID = 0, int animSpeed = 0);
	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();
	virtual void clean() {};


	virtual void collision();
	virtual string type() { return "Player"; };
	
private:
	int m_moveSpeed;

	void handleAnimation();
	void handleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};
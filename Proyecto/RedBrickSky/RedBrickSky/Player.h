#pragma once

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "XboxController.h"

#include "checkML.h"

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

	bool isInteracting() const { return interacting_; }
	void setInteracting(bool b) { interacting_ = b; }

	bool getMoved() const { return moved_; }

	SDL_Rect* getRect() { return &actionRect_; }
	
private:
	int m_moveSpeed;
	bool interacting_;
	bool running_;
	bool text;

	SDL_Rect actionRect_;

	void handleAnimation();
	void updateRect();

	void interacting();

	bool moved_; //Para saber si el jugador se ha movido o no

	Vector2D previousPos_;

};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};
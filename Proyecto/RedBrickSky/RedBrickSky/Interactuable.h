#pragma once

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "checkML.h"

class Interactuable : public GameObject
{
public:
	Interactuable();
	virtual ~Interactuable();

	virtual void load(Vector2D position, int width, int height, std::string id, int numFrames, int callbackID = 0, int animSpeed = 0);
	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();
	virtual void clean();

	virtual void activate();
	void generateCollider();

	void setTileWidth(int t) { tileWidth_ = t; };
	void setTileHeight(int t) { tileHeight_ = t; };

	void changeColliderPos(Vector2D v) { collider_.x = (int)v.getX(); collider_.y = (int)v.getY(); };

	SDL_Rect* getRect() { return &collider_; }

private:
	SDL_Rect collider_; 

protected:
	int tileWidth_;
	int tileHeight_;
};

class InteractuableCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Interactuable();
	}
};

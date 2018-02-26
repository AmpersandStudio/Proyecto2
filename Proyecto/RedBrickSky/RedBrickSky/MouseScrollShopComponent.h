#pragma once
#include "InputComponent.h"
#include "GameManager.h"

class ShopState;

class MouseScrollShopComponent :
	public InputComponent
{
private:
	ShopState* shop;
	vector<estado> states;
	Vector2D pos;
	int objectID;
public:
	MouseScrollShopComponent(ShopState* s, int oID = -1);
	~MouseScrollShopComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
	void move(GameObject* o, int s = 1);

};


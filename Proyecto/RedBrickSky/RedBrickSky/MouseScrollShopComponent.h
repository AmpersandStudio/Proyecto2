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
	int objectID;
public:
	MouseScrollShopComponent(ShopState* s, int oID = -1);
	~MouseScrollShopComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


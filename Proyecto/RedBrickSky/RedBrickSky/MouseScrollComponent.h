#pragma once
#include "InputComponent.h"
#include "GameManager.h"

class ShopState;

class MouseScrollComponent :
	public InputComponent
{
private:
	ShopState* shop;
	vector<estado> states;
	int objectID;
public:
	MouseScrollComponent(ShopState* s, int oID = -1);
	~MouseScrollComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


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
public:
	MouseScrollComponent(ShopState* s);
	~MouseScrollComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


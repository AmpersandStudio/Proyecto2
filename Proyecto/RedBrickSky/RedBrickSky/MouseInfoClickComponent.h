#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "checkML.h"

class ShopState;

class MouseInfoClickComponent :
	public InputComponent
{

private:
	estado st;
	bool active_;
	ShopState* shop_;
public:
	MouseInfoClickComponent(estado s, ShopState* shop = nullptr);
	~MouseInfoClickComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


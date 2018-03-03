#pragma once
#include "InputComponent.h"
#include "GameManager.h"

class MouseInfoClickComponent :
	public InputComponent
{

private:
	estado st;
public:
	MouseInfoClickComponent(estado s);
	~MouseInfoClickComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


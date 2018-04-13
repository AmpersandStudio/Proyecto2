#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "checkML.h"

class MouseInfoClickComponent :
	public InputComponent
{

private:
	estado st;
	bool active_;
public:
	MouseInfoClickComponent(estado s);
	~MouseInfoClickComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


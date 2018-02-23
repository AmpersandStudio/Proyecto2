#pragma once
#include "InputComponent.h"
class MouseInfoClickComponent :
	public InputComponent
{
public:
	MouseInfoClickComponent();
	~MouseInfoClickComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


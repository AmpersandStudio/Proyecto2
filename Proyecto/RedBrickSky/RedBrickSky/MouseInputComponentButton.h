#pragma once
#include "InputComponent.h"
class MouseInputComponentButton :
	public InputComponent
{
public:
	MouseInputComponentButton();
	virtual ~MouseInputComponentButton();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


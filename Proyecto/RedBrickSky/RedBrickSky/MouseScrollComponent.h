#pragma once
#include "InputComponent.h"
class MouseScrollComponent :
	public InputComponent
{
public:
	MouseScrollComponent();
	~MouseScrollComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


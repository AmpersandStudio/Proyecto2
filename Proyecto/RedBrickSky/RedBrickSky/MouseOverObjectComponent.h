#pragma once
#include "InputComponent.h"
class MouseOverObjectComponent :
	public InputComponent
{
public:
	MouseOverObjectComponent();
	~MouseOverObjectComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


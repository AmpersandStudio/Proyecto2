#pragma once
#include "GameObject.h"

class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event) = 0;
};


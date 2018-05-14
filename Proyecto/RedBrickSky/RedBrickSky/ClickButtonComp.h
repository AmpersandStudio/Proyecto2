#pragma once
#include "InputComponent.h"
#include "SoundManager.h"

#include "checkML.h"
class ClickButtonComp :
	public InputComponent
{
public:
	ClickButtonComp();
	~ClickButtonComp();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


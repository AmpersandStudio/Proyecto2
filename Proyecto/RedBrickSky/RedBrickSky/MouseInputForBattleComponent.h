#pragma once
#include "InputComponent.h"
#include "SoundManager.h"

#include "checkML.h"

class MouseInputForBattleComponent :
	public InputComponent
{
public:
	MouseInputForBattleComponent();
	~MouseInputForBattleComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


#pragma once
#include "InputComponent.h"
#include "SoundManager.h"

class MouseInputForBattleComponent :
	public InputComponent
{
public:
	MouseInputForBattleComponent();
	~MouseInputForBattleComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


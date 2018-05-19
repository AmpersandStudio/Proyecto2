#pragma once
#include "InputComponent.h"
#include "SoundManager.h"

#include "checkML.h"

class MouseInputForBattleComponent :
	public InputComponent
{
protected: 
	int a_, b_;
public:
	MouseInputForBattleComponent(int a, int b);
	~MouseInputForBattleComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


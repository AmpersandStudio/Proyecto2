#pragma once
#include "InputComponent.h"
class ControllerForBattleComponent : public InputComponent
{
protected:
	int a_, b_;
public:
	ControllerForBattleComponent(int a, int b);
	~ControllerForBattleComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


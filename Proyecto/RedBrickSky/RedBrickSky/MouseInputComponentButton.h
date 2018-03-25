#pragma once
#include "InputComponent.h"
#include "SoundManager.h"
#include "MainMenuState.h"

class MouseInputComponentButton :
	public InputComponent
{
private: 
	MainMenuState* mainMenu;
	GameObject* obj;

public:
	MouseInputComponentButton(MainMenuState* m = nullptr);
	virtual ~MouseInputComponentButton();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
	void action();
};


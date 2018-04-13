#pragma once
#include "InputComponent.h"
#include "checkML.h"

class KeyInputComponentButton : 
	public InputComponent
{
private:
	SDL_Keycode upLeft_;
	SDL_Keycode downLeft_;
	SDL_Keycode upRight_;
	SDL_Keycode downRight_; 
	SDL_Keycode enter_;

public:
	KeyInputComponentButton(SDL_Keycode upLeft, SDL_Keycode downLeft, SDL_Keycode upRight, SDL_Keycode downRight, SDL_Keycode enter);
	virtual ~KeyInputComponentButton();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


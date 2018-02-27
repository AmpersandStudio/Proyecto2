#pragma once
#include "InputComponent.h"

class KeyInputComponent : public InputComponent
{
private:
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode right_;
	SDL_Keycode left_;

	int rows_; int cols_;
	
public:
	KeyInputComponent(SDL_Keycode up, SDL_Keycode down, SDL_Keycode right, SDL_Keycode left, int rows = 0, int cols = 0);
	virtual ~KeyInputComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


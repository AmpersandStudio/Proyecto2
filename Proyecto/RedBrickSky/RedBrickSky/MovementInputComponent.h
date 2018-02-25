#pragma once
#include "InputComponent.h"
class MovementInputComponent:public InputComponent
{
private:
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode left_;
	SDL_Keycode right_;

public:
	MovementInputComponent(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right);
	~MovementInputComponent();

	bool handleEvent(GameObject* o, const SDL_Event& event);
};


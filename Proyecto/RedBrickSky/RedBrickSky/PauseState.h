#pragma once
#include "GameState.h"

class PauseState :
	public GameState
{
public:
	PauseState();
	virtual ~PauseState();

	virtual bool handleEvent(SDL_Event& event);
	static void resume();
	static void toMenu();
};


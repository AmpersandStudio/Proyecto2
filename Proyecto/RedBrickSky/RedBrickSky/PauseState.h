#pragma once
#include "GameState.h"

#include "checkML.h"

class PauseState :
	public GameState
{
public:
	PauseState();
	virtual ~PauseState();

	virtual bool handleEvent(const SDL_Event& event);
	static void resume();
	static void toMenu();
};


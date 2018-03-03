#pragma once
#include "GameState.h"

class PauseState :
	public GameState
{
public:
	PauseState(Game* gamePtr);
	virtual ~PauseState();

	virtual bool handleEvent(SDL_Event& event);
	static void resume(Game * game);
	static void toMenu(Game* game);
};


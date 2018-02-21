#pragma once
#include "GameState.h"

class PauseState :
	public GameState
{
public:
	PauseState(Game* gamePtr);
	virtual ~PauseState();
};


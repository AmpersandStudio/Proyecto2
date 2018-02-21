#pragma once
#include "GameState.h"

class PlayState :
	public GameState
{
public:
	PlayState(Game* gamePtr);
	virtual ~PlayState();
};


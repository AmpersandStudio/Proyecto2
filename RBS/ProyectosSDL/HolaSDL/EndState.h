#pragma once
#include "GameState.h"

class EndState :
	public GameState
{
public:
	EndState(Game* gamePtr);
	virtual ~EndState();
};


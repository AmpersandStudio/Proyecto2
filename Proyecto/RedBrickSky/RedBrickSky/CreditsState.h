#pragma once
#include "GameState.h"

class CreditsState :
	public GameState
{
public:
	CreditsState(Game* gamePtr);
	virtual ~CreditsState();
};


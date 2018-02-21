#pragma once
#include "GameState.h"

class BackPack :
	public GameState
{
public:
	BackPack(Game* gamePtr);
	virtual ~BackPack();
};


#pragma once
#include "GameState.h"
class PreloadState :
	public GameState
{
public:
	PreloadState(Game* gamePtr);
	virtual ~PreloadState();
};


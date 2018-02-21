#pragma once
#include "GameState.h"

class ShopState :
	public GameState
{
public:
	ShopState(Game* gamePtr);
	virtual ~ShopState();
};


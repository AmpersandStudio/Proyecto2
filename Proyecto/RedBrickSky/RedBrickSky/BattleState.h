#pragma once
#include "GameState.h"

class BattleState :
	public GameState
{
public:
	BattleState(Game* gamePtr);
	virtual ~BattleState();
};


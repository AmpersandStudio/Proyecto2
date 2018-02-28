#pragma once
#include "Game.h"
#include "GameState.h"

class BackManagerState : public GameState
{
public:
	BackManagerState(Game* game);
	~BackManagerState();
	void creaSP();
};


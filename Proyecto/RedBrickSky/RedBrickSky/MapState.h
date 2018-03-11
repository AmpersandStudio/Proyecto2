#pragma once

#include "GameState.h"
#include "Level.h"

class MapState : public GameState
{
public:
	MapState(Game* gamePtr);
	virtual ~MapState();

	virtual void update();
	virtual void render();

private:
	Level* pLevel;
};


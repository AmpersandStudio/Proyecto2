#pragma once

#include "GameState.h"
#include "Level.h"

class MapState : public GameState
{
public:
	MapState();
	virtual ~MapState();

	virtual void update();
	virtual void render();
	virtual bool handleEvent(const SDL_Event& event);

private:
	Level* pLevel;
};


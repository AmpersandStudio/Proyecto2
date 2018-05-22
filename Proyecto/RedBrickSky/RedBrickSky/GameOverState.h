#pragma once
#include "GameState.h"
class GameOverState : public GameState
{
public:
	GameOverState();
	virtual ~GameOverState();

	virtual void render();
	virtual bool handleEvent(const SDL_Event& event);

private:
	static void toGame();
};


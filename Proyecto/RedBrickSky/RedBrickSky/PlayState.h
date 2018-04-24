#pragma once

#include "GameState.h"
#include "GameComponent.h"
#include "Level.h"

#include "checkML.h"

class PlayState : public GameState
{
protected:
	Level * pLevel;

	static void toGame();
	static void toInventary();
	static void toBattle();

public:
	PlayState(int level_);
	virtual ~PlayState();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();
	void actSteps();
	void notOnGrass();
	int getLevel() { return level_; }

private:
	int steps_;
	int level_;
};


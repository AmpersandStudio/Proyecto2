#pragma once

#include "GameState.h"
#include "GameComponent.h"
#include "Level.h"

#include "checkML.h"

class PlayState : public GameState
{
protected:
	std::vector<Level*> pLevels;
	int currentLevel_;
	int lastLevel_;

	static void toGame();
	static void toInventary();
	static void toBattle();

public:
	PlayState();
	virtual ~PlayState();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	void updateAmbienceSounds();
	virtual void render();
	void actSteps();
	void notOnGrass();
	

private:
	int steps_;
	void changeLevel();
};


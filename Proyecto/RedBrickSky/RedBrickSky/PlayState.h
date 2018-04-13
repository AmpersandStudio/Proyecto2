#pragma once

#include "GameState.h"
#include "GameComponent.h"
#include "Level.h"

#include "checkML.h"

class PlayState : public GameState
{
protected:
	//GameComponent* player_;
	Level * pLevel;

	// Métodos
	//void initPlayer();
	static void toGame();
	static void toInventary();
	static void toBattle();

public:
	PlayState();
	virtual ~PlayState();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();
	void actSteps();
	void notOnGrass();

private:
	int steps_;
};


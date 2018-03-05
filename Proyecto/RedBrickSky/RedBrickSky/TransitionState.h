#pragma once
#include "GameState.h"
#include "GameComponent.h"

class TransitionState :
	public GameState
{
private:
	GameComponent* square;

public:
	TransitionState(Game* gamePtr);
	~TransitionState();
	virtual void render();
};

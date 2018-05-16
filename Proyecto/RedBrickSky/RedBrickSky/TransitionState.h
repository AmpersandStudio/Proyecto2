#pragma once
#include "GameState.h"
#include "GameComponent.h"
#include "checkML.h"

class TransitionState : public GameState
{
private:
	GameComponent* square;

public:
	TransitionState(int id);
	~TransitionState();
	virtual void render();
};

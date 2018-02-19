#pragma once
//Estado de pausa del juego.

#include "GameState.h"
class PauseState :
	public GameState
{
public:
	PauseState();
	virtual ~PauseState();
};


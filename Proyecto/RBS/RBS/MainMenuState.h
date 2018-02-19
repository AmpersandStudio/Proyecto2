#pragma once
#include "GameState.h"
//Menu principal del juego, de aquí podemos ir a PlayState, Credits o EndState.

class MainMenuState : GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();
};


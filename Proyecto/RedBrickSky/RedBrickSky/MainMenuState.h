#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
	public GameState
{
public:
	MainMenuState(Game* gamePtr);
	virtual ~MainMenuState();
	static void toGame(Game* game);
	static void exit(Game* game) { game->exitApp(); }; 
	static void toSelector(Game* game);
};


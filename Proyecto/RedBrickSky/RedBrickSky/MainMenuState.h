#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();
	static void toGame();
	static void exit() { Game::Instance()->exitApp(); };
	static void toSelector();
};


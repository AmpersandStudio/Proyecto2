#pragma once
#include "GameState.h"
#include "Button.h"
#include "XboxController.h"
#include "checkML.h"

class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();
	virtual void render();
	static void toGame();
	bool handleEvent(const SDL_Event& event);
	static void exit() { Game::Instance()->exitApp(); };
	static void toCredits();
	static void toggleCtrl() { ctrl_ = !ctrl_; SoundManager::Instance()->playSound("select", 0); }

private:
	static bool ctrl_;	

	int m_joystickDeadZone = XboxController::Instance()->getDeadZone();

	GameComponent* gc;
	InputComponent* ic2;	
	Button* button1;
};


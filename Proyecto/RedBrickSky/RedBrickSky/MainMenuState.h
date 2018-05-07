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
	static void toGame();
	static void toGame2();
	bool handleEvent(const SDL_Event& event);
	static void exit() { Game::Instance()->exitApp(); };
	static void toSelector();
	static void toCredits();
	virtual void update();
	//virtual bool handleEvent(const SDL_Event& event);
private:

	int m_joystickDeadZone = XboxController::Instance()->getDeadZone();

	GameComponent* gc;
	InputComponent* ic2;
	//FUNCIONES PARA MOVER EL RATON MEDIANTE EL MANDO

	
};


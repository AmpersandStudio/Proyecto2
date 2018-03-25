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
	bool handleEvent(const SDL_Event& event);
	static void exit() { Game::Instance()->exitApp(); };
	static void toSelector();
	virtual void update();
	//virtual bool handleEvent(const SDL_Event& event);
private:
	GameComponent* gc;
	InputComponent* ic2;
	//FUNCIONES PARA MOVER EL RATON MEDIANTE EL MANDO
	void initialiseJoysticks();
	void onJoystickAxisMove(SDL_Event event);
	void onJoystickButtonDown(SDL_Event event);
	void onJoystickButtonUp(SDL_Event event);

	bool getButtonState(int joy, int buttonNumber) const { return m_buttonStates[joy][buttonNumber]; }

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	const int m_joystickDeadZone = 10000;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;
};


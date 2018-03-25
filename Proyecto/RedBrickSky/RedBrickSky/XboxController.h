#pragma once
#include <vector>
#include "Vector2D.h"
#include "GameObject.h"
class XboxController
{
	static XboxController* s_pInstance;

public:
	static XboxController* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new XboxController();
		}
		return s_pInstance;
	}
	XboxController();
	~XboxController();

	void insertController();
	void removeController();
	int m_joystickDeadZone = 10000;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::vector<bool>> m_buttonStates;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

	int numControllers;


	bool m_bJoysticksInitialised;

	//Getters del mando de la xbox

	std::vector<SDL_Joystick*> getJoysticks() { return m_joysticks; };
	std::vector<std::vector<bool>> getButtonStates() { return m_buttonStates; };
	std::vector<std::pair<Vector2D*, Vector2D*>> getJoystickValues() {	return m_joystickValues; };

	int getNumControllers() { return numControllers; };
	bool getJoyIni() { return m_bJoysticksInitialised; };

	void onJoystickAxisMove(SDL_Event event);
	void onJoystickButtonDown(SDL_Event event);
	void onJoystickButtonUp(SDL_Event event);

	bool getButtonState(int joy, int buttonNumber) const { return XboxController::Instance()->getButtonStates()[joy][buttonNumber]; }

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	int getDeadZone() { return m_joystickDeadZone; };

};


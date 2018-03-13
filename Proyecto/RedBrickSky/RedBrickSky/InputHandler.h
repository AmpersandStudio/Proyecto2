#pragma once

#include "SDL.H"

#include "Vector2D.h"

#include <iostream>
#include <vector>
#include <utility>

const int m_joystickDeadZone = 10000;

enum mouse_buttons { LEFT, MIDDLE, RIGHT };

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
			return s_pInstance;
		}

		return s_pInstance;
	}

	bool joystickInitialised() const { return m_bJoysticksInitialised; }
	bool getButtonState(int joy, int buttonNumber) const { return m_buttonStates[joy][buttonNumber]; }
	bool getMouseButtonState(int buttonNumber) const { return m_mouseButtonStates[buttonNumber]; }
	bool isKeyDown(SDL_Scancode key);
	Vector2D* getMousePosition() const { return m_mousePosition; }
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	void initialiseJoysticks();
	void update();
	void reset();
	void clean();	
	
private:
	InputHandler();
	~InputHandler() {}
	static InputHandler* s_pInstance;

	void onKeyDown();
	void onKeyUp();

	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	const Uint8* m_keystates;

	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;
};

typedef InputHandler TheInputHandler;


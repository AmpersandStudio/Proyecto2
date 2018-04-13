#include "XboxController.h"


XboxController* XboxController::s_pInstance = 0;

XboxController::XboxController()
{
}


XboxController::~XboxController()
{
}

void XboxController::insertController() {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		SDL_ShowCursor(0);
		numControllers = SDL_NumJoysticks();
		for (size_t i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (joy != NULL)
			{
				m_joysticks.push_back(joy);

				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));

				std::vector<bool> tempButtons;

				for (size_t j = 0; j < SDL_JoystickNumButtons(joy); ++j)
				{
					tempButtons.push_back(false);
				}

				m_buttonStates.push_back(tempButtons);

				tempButtons.clear();
			}
			else
			{
				std::cout << "Joystick load fail! SDL Error: " << SDL_GetError() << "\n";
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << " joystick(s)\n";
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

void XboxController::removeController() {
	if (m_bJoysticksInitialised)
	{
		for (size_t i = 0; i < numControllers; ++i)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}

		numControllers = 0;
		m_joysticks.clear();
		m_bJoysticksInitialised = false;
		m_joystickValues.clear();
		//SDL_JoystickEventState(SDL_DISABLE);
		m_buttonStates.clear();
	}

	SDL_ShowCursor(1);
}

void XboxController::onJoystickButtonDown(SDL_Event event)
{
	//SOLO 1 MANDO
	int whichOne = 0; // event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void XboxController::onJoystickButtonUp(SDL_Event event)
{
	//SOLO UN MANDO
	int whichOne = 0;//event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}

int XboxController::xvalue(int joy, int stick)
{


	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getX();
		}
	}
	return 0;
}

int XboxController::yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}

void XboxController::onJoystickAxisMove(SDL_Event event)
{

	//SOLO 1 MANDO
	int whichOne = 0; //event.jaxis.which;

					  //Left Stick: left / right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}

	//Left Stick: up / down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}

	//Right Stick: left / right
	if (event.jaxis.axis == 2)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}

	//Right Stick: up / down
	if (event.jaxis.axis == 5)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}
}
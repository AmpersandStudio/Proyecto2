#include "ShopXboxControllerComponent.h"



ShopXboxControllerComponent::ShopXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	shop = s;
	ShopItems* items = new ShopItems();
	shopObjects = items->getItems();

	initialiseJoysticks();
}


ShopXboxControllerComponent::~ShopXboxControllerComponent()
{
	clean();
}



void ShopXboxControllerComponent::initialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
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

int ShopXboxControllerComponent::xvalue(int joy, int stick)
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

int ShopXboxControllerComponent::yvalue(int joy, int stick)
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

void ShopXboxControllerComponent::onJoystickAxisMove(SDL_Event event)
{
	int whichOne = event.jaxis.which;

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

void ShopXboxControllerComponent::onJoystickButtonDown(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void ShopXboxControllerComponent::onJoystickButtonUp(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void ShopXboxControllerComponent::clean()
{
	if (m_bJoysticksInitialised)
	{
		for (size_t i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

bool ShopXboxControllerComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;

	if (event.type == SDL_JOYHATMOTION) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		/*	0 -- A
			1 -- B
			2 -- X
			3 -- Y
			4 -- LB
			5 -- RB
			6 -- Back
			7 -- Start
			8 -- Left Joystick Click
			9 -- Right Joystick Click
		*/

		if (event.jhat.value & SDL_HAT_UP) {

			if (posY > Y_)
				posY -= distance;

			if (posX >= Y_) {
				position.setY(posY);
				j--;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_DOWN) {

			if (posY < Y_ + fil_ - 1)
				posY += distance;

			if (posY <= Y_ + fil_) {
				position.setY(posY);
				j++;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_RIGHT) {

			if (posX < X_ + col_ - 1)
				posX += distance / 2;

			if (posX <= X_ + col_ - 1) {
				position.setX(posX);
				i++;
			}

			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_LEFT) {


			if (posX >= X_)
				posX -= distance / 2;

			if (posX >= X_) {
				position.setX(posX);
				i--;
			}

			o->setPosition(position);
		}
	}

	else if (event.type == SDL_JOYBUTTONDOWN) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		onJoystickButtonDown(event);

	 if (getButtonState(0,0)) { //Si se ha pulsado la A
		
			int  p = 0;
			bool encontrado = false;
			while (p < shopObjects.size() && !encontrado) {

				if (shopObjects[p].x == posX && shopObjects[p].y == posY)
					encontrado = true;
				else
					p++;
			}

			if (encontrado) {
				std::cout << shopObjects[savedInvent].nombre << endl;
			
			}
		}
	}
	return handledEvent;
}
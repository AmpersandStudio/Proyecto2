#include "BagXboxControllerComponent.h"



BagXboxControllerComponent::BagXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	back = b;
	shop = s;

	initialiseJoysticks();

}


BagXboxControllerComponent::~BagXboxControllerComponent()
{
	clean();
}


void BagXboxControllerComponent::initialiseJoysticks()
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

int BagXboxControllerComponent::xvalue(int joy, int stick)
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

int BagXboxControllerComponent::yvalue(int joy, int stick)
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

void BagXboxControllerComponent::onJoystickAxisMove(SDL_Event event)
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

void BagXboxControllerComponent::onJoystickButtonDown(SDL_Event event)
{
	int whichOne = event.jaxis.which;
	
	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void BagXboxControllerComponent::onJoystickButtonUp(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void BagXboxControllerComponent::clean()
{
	if (m_bJoysticksInitialised)
	{
		for (size_t i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

bool BagXboxControllerComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;

	if (event.type == SDL_JOYHATMOTION) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		if (event.jhat.value & SDL_HAT_UP) {

			posY -= distance;
			if (posY >= Y_) {
				position.setY(posY);
				j--;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_DOWN) {

			posY += distance;
			if (posY <= col_ * Y_) {
				position.setY(posY);
				j++;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_RIGHT) {

			posX += distance;
			if (posX <= fil_ + X_ + 2) {
				position.setX(posX);
				i++;
			}

			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_LEFT) {


			posX -= distance;
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

		if (getButtonState(0, 0)) { //Si se ha pulsado la A

			invent.clear();
			if (back != nullptr)
				invent = back->getInvent();

			if (selection_) {
				o->setColFrame(0);

				invent[savedInvent].x = posX - 9;
				invent[savedInvent].y = posY;
				invent[savedInvent].mX = i;
				invent[savedInvent].mY = j;


				Vector2D pos(posX, posY);
				invent[savedInvent].GC->setPosition(pos);
				invent[savedInvent].GC->setOriPos(pos);
				selection_ = false;

				if (back != nullptr)
					back->setInvent(invent);
			}

			else {
				int  p = 0;
				bool encontrado = false;
				while (p < invent.size() && !encontrado) {

					if (invent[p].mX == i && invent[p].mY == j)
						encontrado = true;
					else
						p++;
				}

				if (encontrado) {
					o->setColFrame(1);
					savedInvent = p;
					selection_ = true;

				}
			}

			//El siguiente bucle Cambia el color del SP en el que estamos y pone los demás normales (CON TECLADO)
			for (int p = 0; p < SP.size(); p++)
			{
				if (SP[p]->getPosition().getX() == o->getPosition().getX() &&
					SP[p]->getPosition().getY() == o->getPosition().getY()) {

					SP[p]->setColFrame(1);
				}
				else
					SP[p]->setColFrame(0);
			}
		}

		else if (getButtonState(0, 1)) {
			back->elimina();
			back->creaEscena();
		}
	}
	else if (event.type == SDL_JOYBUTTONUP)
		onJoystickButtonUp(event);
	return handledEvent;
}

#include "MainMenuState.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "BackPack.h"
#include "ShopState.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"
#include "NameSelectorState.h"
#include "TextureManager.h"

MainMenuState::MainMenuState()
{
	//Fondo de la tienda
	gc = new GameComponent();
	Vector2D positionGC(0, 0);
	gc->setTextureId("MainMenu");
	gc->addRenderComponent(new RenderFullComponent());

	stage.push_back(gc);

	Button* button0 = new Button("0", toGame, 0);
	Button* button3 = new Button("3", exit, 3);
	Button* button2 = new Button("13", toSelector, 2);

	Vector2D position0(0.9, 2);
	Vector2D position2(0.9, 3.5);
	Vector2D position3(0.9, 5);

	double width = 250;
	double height = 100;

	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic = new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN);
	ic2 = new MouseInputComponentButton(this);

	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic); button0->addInputComponent(ic2);
	button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(rc); button3->addInputComponent(ic); button3->addInputComponent(ic2);
	button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic); button2->addInputComponent(ic2);

	stage.push_back(button0);
	stage.push_back(button3);
	stage.push_back(button2);

	initialiseJoysticks();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::toGame() {
	Game::Instance()->getStateMachine()->pushState(new PlayState());
}

void MainMenuState::toSelector() {
	Game::Instance()->getStateMachine()->pushState(new NameSelectorState());
}

void MainMenuState::update() {
	
}

bool MainMenuState::handleEvent(const SDL_Event& event) {

	bool handleEvent = false;
	
	if (event.type == SDL_JOYBUTTONDOWN) {

		onJoystickButtonDown(event);

		if (getButtonState(0, 1))//Si se ha pulsado la B
			toGame();
		 if (getButtonState(0, 0)) {
			 toGame();
		}

		else if (getButtonState(0, 2)) {
			toSelector();
		}

		else if (getButtonState(0, 3) ) {
			Game::Instance()->exitApp();
			return true;
		}

		onJoystickButtonUp(event);

	}

	else if (event.type == SDL_JOYBUTTONUP)
		onJoystickButtonUp(event);


	//if (event.type == SDL_JOYAXISMOTION) {
	//	onJoystickAxisMove(event);

	//	int x, y;

	//	SDL_GetMouseState(&x, &y);


	//	if (xvalue(0, 1) < 0)
	//	{
	//		SDL_WarpMouseInWindow(Game::Instance()->getWindow(), x - 10, y);
	//	}
	//	else if (xvalue(0, 1) > 0)
	//	{
	//		SDL_WarpMouseInWindow(Game::Instance()->getWindow(), x + 10, y);
	//	}
	//	if (yvalue(0, 1) < 0)
	//	{
	//		SDL_WarpMouseInWindow(Game::Instance()->getWindow(), x, y - 10);
	//	}
	//	else if (yvalue(0, 1) > 0)
	//	{
	//		SDL_WarpMouseInWindow(Game::Instance()->getWindow(), x, y + 10);
	//	}


	//}

	////else if (event.type == SDL_JOYBUTTONDOWN)
	////	ic2->action();
	 if (event.type == SDL_QUIT)
	{
		Game::Instance()->exitApp();
		return true;
	}

	 GameState::handleEvent(event);

	return handleEvent;
}

//METODOS PARA EL MANDO

void MainMenuState::initialiseJoysticks()
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

int MainMenuState::xvalue(int joy, int stick)
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

int MainMenuState::yvalue(int joy, int stick)
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

void MainMenuState::onJoystickAxisMove(SDL_Event event)
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

void MainMenuState::onJoystickButtonDown(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void MainMenuState::onJoystickButtonUp(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}
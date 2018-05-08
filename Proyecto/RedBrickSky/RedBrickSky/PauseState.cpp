#include "PauseState.h"
#include "StateMachine.h"
#include "Button.h"

#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"

PauseState::PauseState()
{
	//	TODO ESTÁ DE PRUEBA EN ESTE MOMENTO
	Button* button0 = new Button("0", resume, 0);
	Button* button3 = new Button("3", toMenu, 3);

	Vector2D position0(0.85, 2.25);
	Vector2D position3(2.25, 2.25);

	SDL_ShowCursor(1);

	double width = 200;
	double height = 100;

	button0->setPosition(position0); button0->setWidth(width); 
	button0->setHeight(height); 
	button0->addRenderComponent(new RenderFrameComponent()); 
	button0->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); 
	button0->addInputComponent(new MouseInputComponentButton());

	button3->setPosition(position3); 
	button3->setWidth(width); 
	button3->setHeight(height); 
	button3->addRenderComponent(new RenderFrameComponent()); 
	button3->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); 
	button3->addInputComponent(new MouseInputComponentButton());
	
	stage.push_back(button0);
	stage.push_back(button3);	

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();
}


PauseState::~PauseState()
{
}

bool PauseState::handleEvent(const SDL_Event & event)
{
	// 1) Comprueba las teclas de acceso a los distintos menús, etc.
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			resume();
		/*else if (event.key.keysym.sym == SDLK_ESCAPE)
			toMenu();*/

	}

	else if (event.type == SDL_JOYBUTTONDOWN) {

		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(0, 0) || XboxController::Instance()->getButtonState(0, 7)) { //Si se ha pulsado la A o de nuevo Start

			resume();
		}

		else if (XboxController::Instance()->getButtonState(0, 1))
		{
			toMenu();
		}

		XboxController::Instance()->onJoystickButtonUp(event); //Aseguro que levantamos el botón después de usarlo
	}
	
	if (event.type == SDL_JOYBUTTONUP)
		XboxController::Instance()->onJoystickButtonUp(event);

	// 2) LLama a los input de cada objeto del propio estado
	return GameState::handleEvent(event);
}

// Te devuelve a la partida (o al estado anterior, más concretamente)
void PauseState::resume() 
{
	Game::Instance()->getStateMachine()->popState();
}

// LLeva al menú principal
void PauseState::toMenu()
{
	while (Game::Instance()->getStateMachine()->size() > 1) // Desapila todos los estados hasta llegar al menú
		Game::Instance()->getStateMachine()->popState();
}

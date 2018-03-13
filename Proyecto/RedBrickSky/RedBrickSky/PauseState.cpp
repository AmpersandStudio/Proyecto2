#include "PauseState.h"
#include "StateMachine.h"
#include "Button.h"

#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"

PauseState::PauseState()
{
	//	TODO EST� DE PRUEBA EN ESTE MOMENTO
	Button* button0 = new Button("0", resume, 0);
	Button* button3 = new Button("3", toMenu, 3);

	Vector2D position0(1, 1);
	Vector2D position3(3, 1);
	Vector2D position2(2, 1);

	double width = 250;
	double height = 200;

	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic = new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN);
	InputComponent* ic2 = new MouseInputComponentButton();

	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic); button0->addInputComponent(ic2);
	button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(rc); button3->addInputComponent(ic); button3->addInputComponent(ic2);
	
	stage.push_back(button0);
	stage.push_back(button3);	
}


PauseState::~PauseState()
{
}

bool PauseState::handleEvent(const SDL_Event & event)
{
	// 1) Comprueba las teclas de acceso a los distintos men�s, etc.
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			Game::Instance()->getStateMachine()->popState();

	}
	// 2) LLama a los input de cada objeto del propio estado
	return GameState::handleEvent(event);
}

// Te devuelve a la partida (o al estado anterior, m�s concretamente)
void PauseState::resume() 
{
	Game::Instance()->getStateMachine()->popState();
}

// LLeva al men� principal
void PauseState::toMenu()
{
	while (Game::Instance()->getStateMachine()->size() > 1) // Desapila todos los estados hasta llegar al men�
		Game::Instance()->getStateMachine()->popState();
}

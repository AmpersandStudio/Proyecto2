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

	Vector2D position0(0.5, 3);
	Vector2D position2(0.5, 4.5);
	Vector2D position3(0.5, 6);

	double width = 220;
	double height = 70;

	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic = new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN);
	ic2 = new MouseInputComponentButton(this);

	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic); button0->addInputComponent(ic2);
	button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(rc); button3->addInputComponent(ic); button3->addInputComponent(ic2);
	button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic); button2->addInputComponent(ic2);

	stage.push_back(button0);
	stage.push_back(button3);
	stage.push_back(button2);

	XboxController::Instance()->insertController();
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

		XboxController::Instance()->onJoystickButtonDown(event);
		

		 if (XboxController::Instance()->getButtonState(0, 0)) {
			 toGame();
		}

		else if (XboxController::Instance()->getButtonState(0, 2)) {
			toSelector();
		}

		else if (XboxController::Instance()->getButtonState(0, 3)) {
			Game::Instance()->exitApp();
			return true;
		}

		XboxController::Instance()->onJoystickButtonUp(event);

	}

	else if (event.type == SDL_JOYBUTTONUP)
		XboxController::Instance()->onJoystickButtonUp(event);

	 if (event.type == SDL_QUIT)
	{
		Game::Instance()->exitApp();
		return true;
	}

	 GameState::handleEvent(event);

	return handleEvent;
}

//METODOS PARA EL MANDO


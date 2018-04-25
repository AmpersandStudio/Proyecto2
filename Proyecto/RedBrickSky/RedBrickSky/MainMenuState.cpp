#include "MainMenuState.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "BackPack.h"
#include "ShopState.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"
#include "NameSelectorState.h"
#include "TextureManager.h"
#include "SoundManager.h"

MainMenuState::MainMenuState()
{
	//Fondo de la tienda
	gc = new GameComponent();
	Vector2D positionGC(0, 0);
	//gc->setTextureId("MainMenu");
	SDL_ShowCursor(1);
	//// New Main Menu
	gc->setTextureId("bgmm");
	gc->addRenderComponent(new RenderFullComponent());

	stage.push_back(gc);

	//Button* button0 = new Button("0", toGame, 0);
	/*Button* button3 = new Button("3", exit, 3);
	Button* button2 = new Button("13", toSelector, 2);*/

	// New Main Menu
	Button* button0 = new Button("nbutton", toGame, 0);
	Button* button3 = new Button("ebutton", exit, 3);
	Button* button2 = new Button("nbutton", toGame2, 0);

	Vector2D position0(0.4, 3);
	Vector2D position2(0.4, 4.5);
	Vector2D position3(0.4, 6);

	double width = 220;
	double height = 70;


	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(new RenderFrameComponent()); button0->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button0->addInputComponent(new MouseInputComponentButton(this));
	button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(new RenderFrameComponent()); button3->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button3->addInputComponent(new MouseInputComponentButton(this));
	button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(new RenderFrameComponent()); button2->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button2->addInputComponent(new MouseInputComponentButton(this));

	stage.push_back(button0);
	stage.push_back(button3);
	stage.push_back(button2);
	button2->setActive(false);

	XboxController::Instance()->insertController();
	SoundManager::Instance()->playMusic("menu", -1);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::toGame() 
{
	SoundManager::Instance()->stopMusic();
	Game::Instance()->getStateMachine()->pushState(new PlayState(0));
}

void MainMenuState::toGame2()
{
	SoundManager::Instance()->stopMusic();
	Game::Instance()->getStateMachine()->pushState(new PlayState(2));
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


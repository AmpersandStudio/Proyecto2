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
#include "CreditsState.h"
#include "QuestionState.h"

MainMenuState::MainMenuState()
{
	//Aquí estoy asegurandome que en el primer estado se crea una única vez los elementos de la tienda
	ShopItems* items = new ShopItems();
	delete items;

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
	Button* button4 = new Button("credits", toCredits, 0);

	Vector2D position0(0.4, 3);
	Vector2D position2(0.4, 4.5);
	Vector2D position3(0.4, 6);

	double width = 220;
	double height = 70;


	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(new RenderFrameComponent()); button0->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button0->addInputComponent(new MouseInputComponentButton(this));
	button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(new RenderFrameComponent()); button3->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button3->addInputComponent(new MouseInputComponentButton(this));
	button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(new RenderFrameComponent()); button2->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button2->addInputComponent(new MouseInputComponentButton(this));
	button4->setPosition(position2); button4->setWidth(width); button4->setHeight(height); button4->addRenderComponent(new RenderFrameComponent()); button4->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN)); button4->addInputComponent(new MouseInputComponentButton(this));

	stage.push_back(button0);
	stage.push_back(button3);
	stage.push_back(button2);
	stage.push_back(button4);
	button2->setActive(false);

	XboxController::Instance()->insertController();
	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->closeChannel(3);
	TheSoundManager::Instance()->playMusic("menu", -1);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::toGame() 
{
	Game::Instance()->getStateMachine()->pushState(new QuestionState());
}

void MainMenuState::toGame2()
{
	Game::Instance()->getStateMachine()->pushState(new PlayState());
}

void MainMenuState::toCredits() {
	Game::Instance()->getStateMachine()->pushState(new CreditsState());
}

bool MainMenuState::handleEvent(const SDL_Event& event) {

	bool handleEvent = false;
	
	if (event.type == SDL_JOYBUTTONDOWN) {

		XboxController::Instance()->onJoystickButtonDown(event);
		

		 if (XboxController::Instance()->getButtonState(0, 0)) {
			 toGame();
		}

		else if (XboxController::Instance()->getButtonState(0, 2)) {
			toCredits();
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

void MainMenuState::render() {

	GameState::render();

	if (XboxController::Instance()->getNumControllers() != 0) {
	
		TheTextureManager::Instance()->drawItem("botonesXbox", 325, 430,
			70, 50, 0, 4, 1, 5, Game::Instance()->getRenderer(), 0, 255);

		TheTextureManager::Instance()->drawItem("botonesXbox", 325, 325,
			70, 50, 0, 3, 1, 5, Game::Instance()->getRenderer(), 0, 255);

		TheTextureManager::Instance()->drawItem("botonesXbox", 325, 220,
			70, 50, 0, 1, 1, 5, Game::Instance()->getRenderer(), 0, 255);
	}

}

//METODOS PARA EL MANDO


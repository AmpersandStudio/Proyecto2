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
	InputComponent* ic2 = new MouseInputComponentButton();

	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic); button0->addInputComponent(ic2);
	button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(rc); button3->addInputComponent(ic); button3->addInputComponent(ic2);
	button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic); button2->addInputComponent(ic2);

	stage.push_back(button0);
	stage.push_back(button3);
	stage.push_back(button2);
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
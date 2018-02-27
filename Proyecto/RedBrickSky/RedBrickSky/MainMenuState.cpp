#include "MainMenuState.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "BackPack.h"
#include "ShopState.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"
#include "NameSelectorState.h"

MainMenuState::MainMenuState(Game* gamePtr) : GameState (gamePtr)
{
	Button* button0 = new Button(gamePtr, toGame, 0);
	Button* button3 = new Button(gamePtr, exit, 3);
	Button* button2 = new Button(gamePtr, toSelector, 2);

	Texture* tx0 = gamePtr->getTexture(0);
	Texture* tx3 = gamePtr->getTexture(3);
	Texture* tx2 = gamePtr->getTexture(13);

	Vector2D position0(1, 1);
	Vector2D position3(3, 1);
	Vector2D position2(2, 1);

	double width = 250;
	double height = 200;

	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic = new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN);
	InputComponent* ic2 = new MouseInputComponentButton();

	button0->setText(tx0); button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic); button0->addInputComponent(ic2);
	button3->setText(tx3); button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(rc); button3->addInputComponent(ic); button3->addInputComponent(ic2);
	button2->setText(tx2); button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic); button2->addInputComponent(ic2);

	stage.push_back(button0);
	stage.push_back(button3);
	stage.push_back(button2);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::toGame(Game* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new PlayState(game));
}

void MainMenuState::toSelector(Game* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new NameSelectorState(game));
}

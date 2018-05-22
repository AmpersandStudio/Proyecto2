#include "GameOverState.h"
#include "Button.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"
#include "StateMachine.h"

GameOverState::GameOverState()
{
	SoundManager::Instance()->playMusic("gameover", -1);

	Button* button0 = new Button("gobutton", toGame, 0);

	Vector2D position0(1.2, 4);

	SDL_ShowCursor(1);

	double width = 245;
	double height = 100;

	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height);
	button0->addRenderComponent(new RenderFrameComponent());
	button0->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	button0->addInputComponent(new MouseInputComponentButton());

	stage.push_back(button0);


}


GameOverState::~GameOverState()
{
}

void GameOverState::render()
{
	TextureManager::Instance()->drawFull("gameover", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
	GameState::render();
}

bool GameOverState::handleEvent(const SDL_Event & event)
{
	return GameState::handleEvent(event);
}

void GameOverState::toGame()
{
	SoundManager::Instance()->stopMusic();
	Game::Instance()->getStateMachine()->popState();
}

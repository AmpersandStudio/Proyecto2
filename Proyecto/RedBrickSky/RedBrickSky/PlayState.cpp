#include "PlayState.h"

#include "Button.h"
#include "StateMachine.h"
#include "KeyInputComponentButton.h"
#include "KeyInputComponent.h"
#include "MouseInputComponentButton.h"
#include "MovementInputComponent.h"
#include "ShopState.h"
#include "BattleState.h"
#include "BackPack.h"
#include "TransitionState.h"
#include "RenderFrameNDComponent.h"
#include "TextureManager.h"
#include "Camera.h"

#include <stdlib.h>
#include <time.h>

PlayState::PlayState(int level)
{
	level_ = level;

	LevelParser levelParser;

	switch (level_)
	{
	case 0:
		pLevel = levelParser.parseLevel("..\\assets\\BetaTutorial.tmx");
		break;

	case 1:
		pLevel = levelParser.parseLevel("..\\assets\\Nivel1.tmx");
		break;

	case 2:
		pLevel = levelParser.parseLevel("..\\assets\\Nivel2.tmx");
		break;
	}

	TheSoundManager::Instance()->playMusic("music", 100);

	steps_ = 0;
	srand(time(NULL));
}

PlayState::~PlayState()
{
	delete pLevel;
}

bool PlayState::handleEvent(const SDL_Event & event)
{
	if (pLevel->getPlayer()->handleEvent(event)) return true;
	

	return GameState::handleEvent(event);
}

void PlayState::update()
{
	pLevel->update();

	GameState::update();
}

void PlayState::actSteps() {
	steps_++;

	int rnd = rand() % 150 + 1;
	if (steps_ > 30 && rnd < steps_)
	{
		pLevel->getPlayer()->setVel(Vector2D(0, 0));
		toBattle();
		steps_ = 0;
	}
}

void PlayState::notOnGrass() {
	
		steps_ = 0;
	
}

void PlayState::render()
{

	switch (level_)
	{
	case 0:
		TextureManager::Instance()->drawFullCamera("level0", Game::Instance()->getRenderer());
		break;

	case 1:
		TextureManager::Instance()->drawFullCamera("level1", Game::Instance()->getRenderer());
		break;

	case 2:
		TextureManager::Instance()->drawFullCamera("level2", Game::Instance()->getRenderer());
		break;
	}

	pLevel->render();
	GameState::render();
}


void PlayState::toGame() {
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new ShopState());
}

void PlayState::toInventary() {
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new BackPack());
}

void PlayState::toBattle() 
{
	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->playMusic("battle", 0);
	TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 2);
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new TransitionState());
}



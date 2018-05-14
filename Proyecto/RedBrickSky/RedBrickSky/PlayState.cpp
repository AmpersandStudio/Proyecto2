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

PlayState::PlayState()
{
	SDL_ShowCursor(0);

	LevelParser levelParser;
	currentLevel_ = GameManager::Instance()->getLevel();
	lastLevel_ = currentLevel_;
	pLevels.resize(7);
	
	pLevels[6] = levelParser.parseLevel("..\\assets\\Tienda.tmx");
	pLevels[5] = levelParser.parseLevel("..\\assets\\Nivel2.tmx");
	pLevels[4] = levelParser.parseLevel("..\\assets\\Gimnasio.tmx");
	pLevels[3] = levelParser.parseLevel("..\\assets\\JardinesSuperiores.tmx");
	pLevels[2] = levelParser.parseLevel("..\\assets\\Pasillos.tmx");
	pLevels[1] = levelParser.parseLevel("..\\assets\\JardinesInferiores.tmx");
	pLevels[0] = levelParser.parseLevel("..\\assets\\Tutorial.tmx");

	TheSoundManager::Instance()->playMusic("music", 100);

	steps_ = 0;
	srand(time(NULL));
}

PlayState::~PlayState()
{
	for (Level* level : pLevels)
	{
		delete level;
	}
}

bool PlayState::handleEvent(const SDL_Event & event)
{
	if (pLevels[currentLevel_]->getPlayer()->handleEvent(event)) return true;
	

	return GameState::handleEvent(event);
}

void PlayState::update()
{
	currentLevel_ = GameManager::Instance()->getLevel();

	if (currentLevel_ != lastLevel_) {
		changeLevel();
	}
	pLevels[currentLevel_]->update();

	

	GameState::update();
}

void PlayState::changeLevel() {

	lastLevel_ = currentLevel_;

	TheCamera::Instance()->setMapDims(pLevels[currentLevel_]->getMapWidth(), pLevels[currentLevel_]->getMapheight());

	pLevels.at(currentLevel_)->getPlayer()->changedlevel();
}

void PlayState::actSteps() {
	steps_++;

	int rnd = rand() % 150 + 1;
	if (steps_ > 30 && rnd < steps_)
	{
		pLevels.at(currentLevel_)->getPlayer()->setVel(Vector2D(0, 0));
		toBattle();
		steps_ = 0;
	}
}

void PlayState::notOnGrass() {
	
		steps_ = 0;
	
}

void PlayState::render()
{
	
	SDL_RenderSetLogicalSize(Game::Instance()->getRenderer(), Game::Instance()->getWinWidth(), Game::Instance()->getWinHeight());

	switch (currentLevel_)
	{
	case 0:
		TextureManager::Instance()->drawFullCamera("level1-1", Game::Instance()->getRenderer());
		break;

	case 1:
		TextureManager::Instance()->drawFullCamera("level1-2", Game::Instance()->getRenderer());
		break;

	case 2:
		TextureManager::Instance()->drawFullCamera("level1-3", Game::Instance()->getRenderer());
		break;

	case 3:
		TextureManager::Instance()->drawFullCamera("level1-4", Game::Instance()->getRenderer());
		break;

	case 4:
		TextureManager::Instance()->drawFullCamera("level1-5", Game::Instance()->getRenderer());
		break;

	case 5:
		TextureManager::Instance()->drawFullCamera("level2", Game::Instance()->getRenderer());
		break;

	case 6:
		TextureManager::Instance()->drawFullCamera("tiendaLevel", Game::Instance()->getRenderer());
		break;
	}

	SDL_RenderSetLogicalSize(Game::Instance()->getRenderer(), Game::Instance()->getWinWidth() / Game::Instance()->getScaleFact(), Game::Instance()->getWinHeight() / Game::Instance()->getScaleFact());

	for (unsigned int i = 0; i < stage.size(); i++) {
		if (stage[i]->getActive())
			stage[i]->render();
	}

	pLevels.at(GameManager::Instance()->getLevel())->render();

	if (GameManager::Instance()->getDialogueState()) {
		GameManager::Instance()->getDialogueCurrent()->render();
	}

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

	if(!GameManager::Instance()->getCharlie()) TheSoundManager::Instance()->playMusic("battle", 0);
	else TheSoundManager::Instance()->playMusic("funk", 0);
	TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 2);
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new TransitionState());
}



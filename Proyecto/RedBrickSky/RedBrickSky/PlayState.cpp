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
#include "GameOverState.h"
#include "OutroState.h"

#include <stdlib.h>
#include <time.h>

PlayState::PlayState()
{

	TheSoundManager::Instance()->stopMusic();
	SDL_ShowCursor(0);

	LevelParser levelParser;
	currentLevel_ = GameManager::Instance()->getLevel();
	lastLevel_ = currentLevel_;
	pLevels.resize(8);
	
	pLevels[7] = levelParser.parseLevel("..\\assets\\PasilloFinal.tmx");
	pLevels[6] = levelParser.parseLevel("..\\assets\\Tienda.tmx");
	if (GameManager::Instance()->getLevel() == GameManager::TUTORIAL) pLevels[5] = levelParser.parseLevel("..\\assets\\Nivel2.tmx");
	pLevels[4] = levelParser.parseLevel("..\\assets\\Gimnasio.tmx");
	pLevels[3] = levelParser.parseLevel("..\\assets\\JardinesSuperiores.tmx");
	pLevels[2] = levelParser.parseLevel("..\\assets\\Pasillos.tmx");
	pLevels[1] = levelParser.parseLevel("..\\assets\\JardinesInferiores.tmx");
	pLevels[0] = levelParser.parseLevel("..\\assets\\Tutorial.tmx");
	if (GameManager::Instance()->getLevel() == GameManager::CLASES) pLevels[5] = levelParser.parseLevel("..\\assets\\Nivel2.tmx");
	

	if (GameManager::Instance()->getLevel() == GameManager::CLASES)
	{
		updateAmbienceSounds(5, 0);
	}
	else
	{
		updateAmbienceSounds(currentLevel_, lastLevel_);
	}
	

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
	if (GameManager::Instance()->getEnd())
	{
		Game::Instance()->getStateMachine()->changeState(new OutroState());
		return;
	}

	currentLevel_ = GameManager::Instance()->getLevel();

	if (GameManager::Instance()->getGameOver()) toGameOver();

	if (currentLevel_ != lastLevel_) {
		updateAmbienceSounds(currentLevel_, lastLevel_);
		changeLevel();
	}
	pLevels[currentLevel_]->update();

	if (!TheSoundManager::Instance()->isPlayingChannel(3)) {
		updateAmbienceSounds(currentLevel_, lastLevel_);
	}

	GameState::update();
}

void PlayState::updateAmbienceSounds(int currentLvl, int lastLvl) {


//Música de fondo

	//Estados
	enum stateChanges {INTERIOR_TO_EXTERIOR, EXTERIOR_TO_INTERIOR, NO_CHANGE};
	stateChanges state = NO_CHANGE;

	if ( (currentLvl == 0 || currentLvl == 1 || currentLvl == 3) && (lastLvl != 0 && lastLvl != 1 && lastLvl != 3) ) {
		state = INTERIOR_TO_EXTERIOR;
	}
	else if ((currentLvl != 0 && currentLvl != 1 && currentLvl != 3) && (lastLvl == 0 || lastLvl == 1 || lastLvl == 3)) {
		state = EXTERIOR_TO_INTERIOR;
	}

	switch (state){

	case INTERIOR_TO_EXTERIOR:
		currMusic_ = "music";
		TheSoundManager::Instance()->stopMusic();
		break;

	case EXTERIOR_TO_INTERIOR:
		currMusic_ = "music2";
		TheSoundManager::Instance()->stopMusic();
		break;

	case NO_CHANGE:
		break;
	}

	//Actualización de la música de fondo
	if (!TheSoundManager::Instance()->isPlayingMusic()) {
		TheSoundManager::Instance()->playMusic(currMusic_, -1);
	}


//Sonidos de ambiente
	StateMachine* sm = Game::Instance()->getStateMachine();
	if (sm->currentState() == this) {
		TheSoundManager::Instance()->closeChannel(3);
		if (currentLvl == 0 || currentLvl == 1 || currentLvl == 3 ) {
			TheSoundManager::Instance()->PlaySoundInChannel(3, "exteriores", -1);
		}
		else {
			TheSoundManager::Instance()->PlaySoundInChannel(3, "interiores", -1);
		}
	}

}

void PlayState::changeLevel() {

	lastLevel_ = currentLevel_;

	TheCamera::Instance()->setMapDims(pLevels[currentLevel_]->getMapWidth(), pLevels[currentLevel_]->getMapheight());

	pLevels.at(currentLevel_)->getPlayer()->changedlevel();
}

void PlayState::actSteps() {
	steps_++;

	int rnd = rand() % 250 + 1;
	if (steps_ > 70 && rnd < steps_)
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

	case 7:
		TextureManager::Instance()->drawFullCamera("level3", Game::Instance()->getRenderer());
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
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new TransitionState(0));
}

void PlayState::toGameOver()
{
	GameManager::Instance()->setGameOver(false);
	pLevels[currentLevel_]->getPlayer()->resetPlayer();
	Game::Instance()->getStateMachine()->pushState(new GameOverState());
}



#include "GameManager.h"
#include "TransitionState.h"
#include "StateMachine.h"

GameManager* GameManager::s_pInstance = 0;


vector<estado> GameManager::copyInventory() { // no queréis que const vector<estado> & GameManager::copyInventory()
	return inventory;
}

void GameManager::toBattle()
{
	TheSoundManager::Instance()->stopMusic();
	/*TheSoundManager::Instance()->playMusic("trans_btl", 0);*/
	TheSoundManager::Instance()->playMusic("battle", 0);
	TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 2);
	Game::Instance()->getStateMachine()->pushState(new TransitionState());
}

void GameManager::exitBattle()
{
	if (currentNPC != nullptr) {
		currentNPC->isDefeated();
		currentNPC = nullptr;
	}
}

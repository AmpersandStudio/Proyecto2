#include "GameManager.h"
#include "TransitionState.h"
#include "StateMachine.h"

GameManager* GameManager::s_pInstance = 0;


vector<estado> GameManager::copyInventory() { // no queréis que const vector<estado> & GameManager::copyInventory()
	return inventory;
}

vector<estado> GameManager::copyShopItems() { // no queréis que const vector<estado> & GameManager::copyInventory()
	return shopObjects;
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
	if (currentInter != nullptr) {
		currentInter->isDefeated();
		currentInter = nullptr;
	}
}

int GameManager::getEnemy()
{
	int rnd;

	switch (level_)
	{
	case 0:
		rnd = rand() % 2;
		if (rnd == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
		break;

	case 1:
		rnd = rand() % 2;
		if (rnd == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
		break;

	case 2:
		rnd = rand() % 3;
		if (rnd == 0)
		{
			return 2;
		}
		else if (rnd == 1)
		{
			return 3;
		}
		else
		{
			return 4;
		}
		break;

	case 3:
		rnd = rand() % 3;
		if (rnd == 0)
		{
			return 0;
		}
		else if (rnd == 1)
		{
			return 1;
		}
		else
		{
			return 5;
		}
		break;

	case 4:
		rnd = rand() % 2;
		if (rnd == 0)
		{
			return 4;
		}
		else
		{
			return 5;
		}
		break;

	case 5:
		rnd = rand() % 6;
		if (rnd == 0)
		{
			return 3;
		}
		else if (rnd == 1)
		{
			return 4;
		}
		else if (rnd == 2)
		{
			return 6;
		}
		else if (rnd == 3)
		{
			return 7;
		}
		else if (rnd == 4)
		{
			return 8;
		}
		else
		{
			return 9;
		}
		break;
	}	
}

bool GameManager::checkEasterEgg()
{
	bool check = true;
	for (size_t i = 0; i < 4; i++)
	{
		check = check && easterEgg[i];
	}
	return check;
}

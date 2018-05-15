#include "GameManager.h"
#include "TransitionState.h"
#include "StateMachine.h"
#include "ShopItems.h"

GameManager* GameManager::s_pInstance = 0;


vector<estado> GameManager::copyInventory() { // no queréis que const vector<estado> & GameManager::copyInventory()
	return inventory;
}

vector<estado> GameManager::copyShopItems() { // no queréis que const vector<estado> & GameManager::copyInventory()
	return shopObjects;
}

void GameManager::toBattle()
{
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

void GameManager::setBattlePlayer(int t, int atk, int def, int spd, int hp)
{
	playerType = t;
	playerAttack = atk;
	playerDeffense = def;
	playerSpeed = spd;
	playerHP = hp;
	playerMaxHP = hp;
}

void GameManager::resetGame()
{
	shopObjects.clear();
	ShopItems si = ShopItems();
	inventory.clear();
	money = 500;
	potions_ = 0;
	potionsPrize = 100;
	playerType = 0;
	playerAttack = 12;
	playerDeffense = 12;
	playerSpeed = 12;
	playerHP = 260;
	playerMaxHP = 260;
	name = "";
	atSound = "";
	doors.clear();
	level_ = TUTORIAL;
	dialogueActive = false;
	currentInter = nullptr;
	currentDialogue_ = nullptr;
	ampersand_ = false;
	easterEgg[0] = false;
	easterEgg[1] = false;
	easterEgg[2] = false;
	easterEgg[3] = false;
	charlie_ = false;
	first_ = false;
	question_ = false;
	last_ = false;
}

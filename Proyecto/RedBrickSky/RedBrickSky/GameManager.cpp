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

void GameManager::toBattle(int id)
{
	Game::Instance()->getStateMachine()->pushState(new TransitionState(id));
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

void GameManager::setAmpersand()
{
	ampersand_ = true;

	estado n;
	n.price = 0;
	n.comprado = true;
	n.ID = 16;
	n.empty = false;
	n.mX = 0;
	n.mY = 0;
	n.w = 45;
	n.h = 45;
	n.tx = "21";
	n.type = 0;
	n.nombre = "Ampergun";
	n.FilFrame = 4;
	n.colFrame = 1;
	setInventory(n);
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
	for (size_t i = 0; i < doors.size(); i++)
	{
		doors.at(i) = false;
	}

	level_ = TUTORIAL;
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

	currentInter = nullptr;
	currentDialogue_ = nullptr;

	gameOver_ = false;
	dialogueActive = false;
	ampersand_ = false;
	easterEgg[0] = false;
	easterEgg[1] = false;
	easterEgg[2] = false;
	easterEgg[3] = false;
	charlie_ = false;
	first_ = false;
	question_ = false;
	last_ = false;
	endGame_ = false;
	doorColl_ = false;
}

void GameManager::toLevel2()
{
	shopObjects.clear();
	ShopItems si = ShopItems();
	inventory.clear();
	for (size_t i = 0; i < doors.size(); i++)
	{
		doors.at(i) = false;
	}
	doors.at(8) = true;
	doors.at(13) = true;

	level_ = CLASES;
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

	currentInter = nullptr;
	currentDialogue_ = nullptr;

	gameOver_ = false;
	dialogueActive = false;
	ampersand_ = false;
	easterEgg[0] = false;
	easterEgg[1] = false;
	easterEgg[2] = false;
	easterEgg[3] = false;
	charlie_ = false;
	first_ = false;
	question_ = false;
	last_ = false;
	endGame_ = false;
	ampersand_ = true;
	doorColl_ = false;

	estado n;
	n.price = 0;
	n.comprado = true;
	n.ID = 16;
	n.empty = false;
	n.mX = 0;
	n.mY = 0;
	n.w = 45;
	n.h = 45;
	n.tx = "21";
	n.type = 0;
	n.nombre = "Ampergun";
	n.FilFrame = 4;
	n.colFrame = 1;
	setInventory(n);
}
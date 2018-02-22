#include "GameManager.h"

GameManager* GameManager::s_pInstance = 0;



GameManager::~GameManager()
{
}


vector<estado> GameManager::copyInventory() {
	return inventory;
}

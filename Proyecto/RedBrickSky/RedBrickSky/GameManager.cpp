#include "GameManager.h"

GameManager* GameManager::s_pInstance = 0;


vector<estado> GameManager::copyInventory() { // no queréis que const vector<estado> & GameManager::copyInventory()
	return inventory;
}
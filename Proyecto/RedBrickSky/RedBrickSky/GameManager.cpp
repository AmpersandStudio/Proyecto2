#include "GameManager.h"

GameManager* GameManager::s_pInstance = 0;


vector<estado> GameManager::copyInventory() {
	return inventory;
}
vector<estado> GameManager::copyShopObjects() {
	return shopObjects;
}
#include "Teleport.h"
#include "GameManager.h"



Teleport::Teleport()
{
}


Teleport::~Teleport()
{
}

void Teleport::selectAction()
{
	if (keyID_ == 0 || GameManager::Instance()->getDoor(keyID_))
		GameManager::Instance()->setCurrentLevel(changeLevel);
}

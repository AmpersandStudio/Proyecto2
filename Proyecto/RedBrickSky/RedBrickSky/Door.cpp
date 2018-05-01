#include "Door.h"
#include "GameManager.h"
#include "Camera.h"

void Door::activate()
{
	 
}

void Door::render()
{
	TheTextureManager::Instance()->drawFull("door", 
		(Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX(),
		(Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(),
		64, 32, TheGame::Instance()->getRenderer(), 0, 255);
}

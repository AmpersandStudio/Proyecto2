#include "Door.h"
#include "GameManager.h"
#include "Camera.h"

void Door::activate()
{
	if (GameManager::Instance()->getKey(id_))
	{
		GameManager::Instance()->setKey(id_);
		active_ = true;
	}
	
}

void Door::render()
{
	if (!active_)
	{
		TheTextureManager::Instance()->drawFull("door",
			(Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX(),
			(Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(),
			64, 32, TheGame::Instance()->getRenderer(), 0, 255);
	}
}

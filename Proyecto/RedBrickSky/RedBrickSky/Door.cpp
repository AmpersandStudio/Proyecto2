#include "Door.h"
#include "GameManager.h"
#include "Camera.h"

void Door::activate()
{

	if (!active_)
	{
		if (GameManager::Instance()->getDoor(keyID_))
		{
			//GameManager::Instance()->setDoor(keyID_);
			TheSoundManager::Instance()->playSound("Puerta_abrir", 0);
			active_ = true;
		}
		else
		{
			if (!dialogueActive_ && !GameManager::Instance()->getDialogueState())
			{
				dialogueActive_ = true;
				GameManager::Instance()->setDialogueState(true, &text);
				//DESCOMENTAR ESTO CUANDO SE VUELVA A PODER PARAR A LOS NPCs TETES 
			}
			else if (dialogueActive_)
			{
				dialogueActive_ = text.nextDialogue();
				if (!dialogueActive_)
				{
					GameManager::Instance()->setDialogueState(false, nullptr);
				}
			}
		}
	}
}

void Door::update()
{
	if (dialogueActive_) {
		text.setX(position_.getX());
		text.setY(position_.getY());
		if (!text.isActive()) {
			text.update();
		}
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

		/*if (dialogueActive_ && GameManager::Instance()->getDialogueState()) {
			text.render();
		}*/
	}
}

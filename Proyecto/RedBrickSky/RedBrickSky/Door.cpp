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
				TheSoundManager::Instance()->playSound("dialogo", 0);
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
		Interactuable::render();
	}
}

#include "Teleport.h"
#include "GameManager.h"



Teleport::Teleport()
{
}


Teleport::~Teleport()
{
}

void Teleport::update()
{
	if (dialogueActive_) {
		text.setX(position_.getX());
		text.setY(position_.getY());
		if (!text.isActive()) {
			text.update();
		}
	}
}

void Teleport::render()
{
	if (isActive_)
	{
		Interactuable::render();
		/*TheTextureManager::Instance()->drawFull("door",
		(Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX(),
		(Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(),
		64, 32, TheGame::Instance()->getRenderer(), 0, 255);*/

		/*if (dialogueActive_ && GameManager::Instance()->getDialogueState()) {
		text.render();
		}*/
	}
}

void Teleport::activate()
{

	/*StringToScreen::Instance()->setMessageAt(Message_, position_.getX(), position_.getY());
	StringToScreen::Instance()->startMessagin();*/

	std::cout << Msg_ << endl;
	if (keyID_ == 0 || !GameManager::Instance()->getDoor(keyID_))
	{
		if (!hasDialogue)
			selectAction();
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
					selectAction();
				}
			}
		}
	}
	else
	{
		TheSoundManager::Instance()->playSound("Puerta_abrir", 0);
		SDL_Delay(800);
		GameManager::Instance()->setCurrentLevel(changeLevel);
		isActive_ = false;
	}
}

void Teleport::selectAction()
{
	if (keyID_ == 0 || GameManager::Instance()->getDoor(keyID_))
	{
		TheSoundManager::Instance()->playSound("Puerta_abrir", 0);
		SDL_Delay(800);
		GameManager::Instance()->setCurrentLevel(changeLevel);
		isActive_ = false;
	}
}

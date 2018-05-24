#include "Cartel.h"
#include "Game.h"
#include "StateMachine.h"
#include "ShopState.h"
#include "playState.h"
#include "Camera.h"

Cartel::Cartel() : dialogueActive_(false), isFighter_(false), hasDialogue(false), keyID_(0), toShop(false)
{
	timeStart_ = SDL_GetTicks();
	timeDisplayInterval_ = 700;
	col_ = 0;
	changed_ = true;
	cleon_ = false;
	nugget_ = -1;
}


Cartel::~Cartel()
{
}

void Cartel::activate()
{

	/*StringToScreen::Instance()->setMessageAt(Message_, position_.getX(), position_.getY());
	StringToScreen::Instance()->startMessagin();*/

	if (cleon_ && !GameManager::Instance()->getAmpersand())
	{
		if (GameManager::Instance()->checkEasterEgg())
		{
			Msg_.append("B");
			text = Dialogue(Msg_);
			GameManager::Instance()->setAmpersand();
		}
	}

	if (nugget_ != -1) GameManager::Instance()->setEasterEgg(nugget_);

	//std::cout << Msg_ << endl;

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

void Cartel::selectAction()
{
	if (isFighter_)
	{
		GameManager::Instance()->getInteractuable(this);
		GameManager::Instance()->toBattle(battleId);
	}
	else if (toShop)
	{
		//SoundManager::Instance()->stopMusic();
		TheGame::Instance()->getStateMachine()->pushState(new ShopState());
	}
	else if (!isFighter_ && keyID_ != 0)
		GameManager::Instance()->setDoor(keyID_);
}

void Cartel::render()
{
	if (isActive_) Interactuable::render();

	if (hasDialogue)
	{
		/*if (dialogueActive_ && GameManager::Instance()->getDialogueState())
		{
			text.render();
		}*/
	}
}

void Cartel::update()
{
	if (((timeStart_ + timeDisplayInterval_) <= SDL_GetTicks()))
	{
		setColFrame(col_);
		change();
		timeStart_ = SDL_GetTicks();
	}

	if (hasDialogue)
	{
		if (dialogueActive_)
		{
			text.setX(position_.getX());
			text.setY(position_.getY());

			if (!text.isActive())
				text.update();
		}
	}
}

void Cartel::change()
{

	changed_ = !changed_;
	if (changed_) col_ = 0;
	else col_ = 1;

}

void Cartel::isDefeated()
{
	isFighter_ = false;
	Msg_.append("B");
	text = Dialogue(Msg_);

	if (keyID_ != 0)
		GameManager::Instance()->setDoor(keyID_);
}

void Cartel::setMSG(std::string msg)
{
	Msg_ = msg;

	if (Msg_ != " ")
	{
		text = Dialogue(Msg_);
		hasDialogue = true;
	}
	else
		Dialogue("NULL");
}

void Cartel::generateCollider()
{
	Interactuable::generateCollider();
}
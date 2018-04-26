#include "Cartel.h"
#include "Game.h"
#include "StateMachine.h"
#include "ShopState.h"
#include "playState.h"
#include "Camera.h"

Cartel::Cartel()
{

}


Cartel::~Cartel()
{
}

void Cartel::activate() {

	/*StringToScreen::Instance()->setMessageAt(Message_, position_.getX(), position_.getY());
	StringToScreen::Instance()->startMessagin();*/

	if (toShop == 1) {
		SoundManager::Instance()->stopMusic();
		GameManager::Instance()->setCurrentLevel(3);

	}
	else if (tenderMan)
		TheGame::Instance()->getStateMachine()->pushState(new ShopState());

	else if (toPlayGround) {
		GameManager::Instance()->setCurrentLevel(0);
	}
}

void Cartel::render()
{

}

void Cartel::generateCollider()
{
Interactuable::generateCollider();
}
#include "Cartel.h"
#include "Game.h"
#include "StateMachine.h"
#include "ShopState.h"
#include "playState.h"

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
		Game::Instance()->getStateMachine()->pushState(new PlayState(3));
	}
	else if(tenderMan)
		TheGame::Instance()->getStateMachine()->pushState(new ShopState());
}
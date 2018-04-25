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
	//if (tenderMan)
	//{
	//	SDL_Rect fillRect = { (Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX() , (Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(), 110, 160 };
	//	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0x00, 0xFF, 0xFF);
	//	SDL_RenderFillRect(Game::Instance()->getRenderer(), &fillRect);
	//}
}

void Cartel::generateCollider()
{
	if (tenderMan)
	{
		collider_.x = position_.getX();
		collider_.y = position_.getY();
		collider_.w = 110;
		collider_.h = 160;
	}
	else
	{
		Interactuable::generateCollider();
	}
}
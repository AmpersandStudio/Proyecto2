#include "Cartel.h"
#include "Game.h"
#include "StateMachine.h"
#include "ShopState.h"
#include "playState.h"
#include "Camera.h"

Cartel::Cartel()
{
	timeStart_ = SDL_GetTicks();
	timeDisplayInterval_ = 700;
	col_ = 0;
	changed_ = true;
}


Cartel::~Cartel()
{
}

void Cartel::activate() {

	/*StringToScreen::Instance()->setMessageAt(Message_, position_.getX(), position_.getY());
	StringToScreen::Instance()->startMessagin();*/

	std::cout << Message_ << endl;

	std::cout << "Hola me has interactuado" << endl;

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
	if (isActive_) Interactuable::render();
}

void Cartel::update() {
	if (((timeStart_ + timeDisplayInterval_) <= SDL_GetTicks()))
	{
		setColFrame(col_);
		change();
		timeStart_ = SDL_GetTicks();
	}
}

void Cartel::change() {

	changed_ = !changed_;
	if (changed_) col_ = 0;
	else col_ = 1;

}

void Cartel::generateCollider()
{
	Interactuable::generateCollider();
}
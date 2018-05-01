#include "Key.h"

Key::Key()
{
	setActive(true);
	timeStart_ = SDL_GetTicks();
	timeDisplayInterval_ = 700;
	col_ = 0;
	changed_ = true;
}


Key::~Key()
{
}

void Key::render()
{
	if (isActive_) Interactuable::render();
}

void Key::update() {

	if (((timeStart_ + timeDisplayInterval_) <= SDL_GetTicks()))
	{
		setColFrame(col_);
		change();
		timeStart_ = SDL_GetTicks();
	}

}

void Key::change() {

	changed_ = !changed_;
	if (changed_) col_ = 0;
	else col_ = 1;


}

void Key::activate()
{
	if (isActive_)
	{
		GameManager::Instance()->setKey(keyID);
		setActive(false);
	}
}

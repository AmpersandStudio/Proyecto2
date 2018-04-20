#include "Key.h"



Key::Key()
{
	setActive(true);
}


Key::~Key()
{
}

void Key::render()
{
	if (isActive_) Interactuable::render();
}

void Key::activate()
{
	if (isActive_)
	{
		GameManager::Instance()->getDoors()[keyID] = true;
		setActive(false);
	}
}

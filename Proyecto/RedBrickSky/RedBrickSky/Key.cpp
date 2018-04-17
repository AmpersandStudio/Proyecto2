#include "Key.h"



Key::Key()
{
}


Key::~Key()
{
}

void Key::activate()
{
	GameManager::Instance()->getDoors()[keyID] = true;
}

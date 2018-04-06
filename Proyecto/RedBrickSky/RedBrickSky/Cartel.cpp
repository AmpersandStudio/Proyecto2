#include "Cartel.h"
#include "Game.h"
#include "StateMachine.h"
#include "ShopState.h"


Cartel::Cartel()
{
}


Cartel::~Cartel()
{
}

void Cartel::activate() {
	std::cout << Message_ << endl;
	TheGame::Instance()->getStateMachine()->pushState(new ShopState());
}
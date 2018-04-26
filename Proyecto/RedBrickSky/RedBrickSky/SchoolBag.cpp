#include "SchoolBag.h"

SchoolBag::SchoolBag()
{
}


SchoolBag::~SchoolBag()
{
}

void SchoolBag::activate() {

	StringToScreen::Instance()->renderBackGround();
	StringToScreen::Instance()->setMessage("Has recogido: " + std::to_string(Sweeties_) + " caramelos!");
	StringToScreen::Instance()->startMessagin();

	GameManager::Instance()->addMoney(Sweeties_);
	Sweeties_ = 0;
}
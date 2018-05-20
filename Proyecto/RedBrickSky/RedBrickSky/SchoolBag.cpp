#include "SchoolBag.h"

SchoolBag::SchoolBag()
{
}


SchoolBag::~SchoolBag()
{
}

void SchoolBag::activate() {

	if (Sweeties_ > 0) {

		TheSoundManager::Instance()->playSound("monedas", 0);
		std::cout << "Has recogido: " + std::to_string(Sweeties_) + " caramelos!" << endl;

		StringToScreen::Instance()->renderBackGround();
		StringToScreen::Instance()->setMessageAt("Has recogido: " + std::to_string(Sweeties_) + " caramelos!", 20, 20);
		StringToScreen::Instance()->startMessagin();

		GameManager::Instance()->addMoney(Sweeties_);
		Sweeties_ = 0;
	}

}
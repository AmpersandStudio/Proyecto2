#include "SchoolBag.h"

SchoolBag::SchoolBag()
{
}


SchoolBag::~SchoolBag()
{
}

void SchoolBag::activate() {
	std::cout << "Has recogido: " << Sweeties_ << " caramelos!" << endl;
	GameManager::Instance()->addMoney(Sweeties_);
	Sweeties_ = 0;
}
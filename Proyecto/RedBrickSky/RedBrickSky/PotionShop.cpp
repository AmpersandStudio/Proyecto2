#include "PotionShop.h"
#include "GameManager.h"


PotionShop::PotionShop()
{
	
}


PotionShop::~PotionShop()
{
}

bool PotionShop::handleEvent(GameObject* o, const SDL_Event& event) {

	bool handledEvent = false;
	o->setColFrame(0);

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		Vector2D position = o->getPosition();
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos estado del raton
		//comprobamos estado del raton
		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight())) {
			o->setColFrame(1);
			if (GameManager::Instance()->getMoney() >= GameManager::Instance()->getPotionsPrize()) {
				GameManager::Instance()->addPotion();
				GameManager::Instance()->setMoney(GameManager::Instance()->getMoney() - GameManager::Instance()->getPotionsPrize());
				StringToScreen::Instance()->setMessage("¡Pocion comprada! ");
				StringToScreen::Instance()->startMessagin();
				StringToScreen::Instance()->changeInfinite(0, "Caramelos: " + std::to_string(GameManager::Instance()->getMoney()));
				StringToScreen::Instance()->changeInfinite(1, "Comprar pociones      x" + std::to_string(GameManager::Instance()->getPotions()));
			}
			else {
				StringToScreen::Instance()->setMessage("¡No tienes más dinero! ");
				StringToScreen::Instance()->startMessagin();
			}
		}
	}
	
	else if (event.type == SDL_MOUSEMOTION)
	{
		Vector2D position = o->getPosition();
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos estado del raton
		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight())) {
			o->setColFrame(1);
		}
	}

	return handledEvent;
}

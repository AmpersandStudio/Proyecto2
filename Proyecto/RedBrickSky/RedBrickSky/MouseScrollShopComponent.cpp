#include "MouseScrollShopComponent.h"
#include "ShopState.h"

MouseScrollShopComponent::MouseScrollShopComponent(ShopState* s, int oID)
{
	shop = s;
	objectID = oID;
	moves_ = 0;

}


MouseScrollShopComponent::~MouseScrollShopComponent()
{
}

bool MouseScrollShopComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	states = shop->getSP();

	bool handledEvent = false;
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton
	pos = o->getPosition();
	
	
		if (event.wheel.y == 1) // scroll up
		{
			if (x < Game::Instance()->getWinWidth() / 3 && pos.getX() * o->getWidth() < Game::Instance()->getWinWidth() / 3) {

				if (moves_ < 3) {
					move(o, -1);
					moves_++;
				}
				//ultimaFilaY -= 20;
			}

			else if (x >= Game::Instance()->getWinWidth() / 3 && pos.getX() * o->getWidth() >= Game::Instance()->getWinWidth() / 3)
				move(o, -1);
			//ultimaFilaY -= 20;
		}


		else if (event.wheel.y == -1) // scroll down
		{
			if (x < Game::Instance()->getWinWidth() / 3 && pos.getX() * o->getWidth() < Game::Instance()->getWinWidth() / 3) {

				if (moves_ > 0) {
					move(o);
					moves_--;
				}
			}
				//ultimaFilaY += 20;

			else if (x >= Game::Instance()->getWinWidth() / 3 && pos.getX() * o->getWidth() >= Game::Instance()->getWinWidth() / 3)
				move(o);

				//ultimaFilaY -= 20;
			}
		
		//std::cout << moves_ << endl;
	
	
	return handledEvent;
}

	void MouseScrollShopComponent::move(GameObject* o, int s) {

		pos.setY(pos.getY() + 2 * s);
		o->setPosition(pos);
		int i = 0;
		bool encontrado = false;

		if (objectID != -1) {

				states[objectID].y = pos.getY();
				shop->setSP(states);
		}

		o->setOriPos(pos);
	}

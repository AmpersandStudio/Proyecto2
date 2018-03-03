#include "MouseScrollShopComponent.h"
#include "ShopState.h"

MouseScrollShopComponent::MouseScrollShopComponent(ShopState* s, int oID)
{
	shop = s;
	objectID = oID;

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
		if (x < o->getGame()->getWinWidth() / 2 && pos.getX() * o->getWidth() < o->getGame()->getWinWidth() / 2) {

			move(o, -1);
			//ultimaFilaY -= 20;
		}

		else if(x >= o->getGame()->getWinWidth() / 2 && pos.getX() * o->getWidth() >= o->getGame()->getWinWidth() / 2)
			move(o, -1);
			//ultimaFilaY -= 20;
	}


	else if (event.wheel.y == -1) // scroll down
	{
		if (x < o->getGame()->getWinWidth() / 2 && pos.getX() * o->getWidth() < o->getGame()->getWinWidth() / 2)
			move(o);

			//ultimaFilaY += 20;

		else if(x >= o->getGame()->getWinWidth() / 2 && pos.getX() * o->getWidth() >= o->getGame()->getWinWidth() / 2)
			move(o);

			//ultimaFilaY -= 20;
	}

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

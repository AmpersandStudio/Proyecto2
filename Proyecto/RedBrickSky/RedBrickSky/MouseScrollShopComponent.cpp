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
	//states = shop->getSP();

	bool handledEvent = false;
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton
	Vector2D pos = o->getPosition();

	if (event.wheel.y == 1) // scroll up
		{
		if (x < o->getGame()->getWinWidth() / 2 && pos.getX()  * o->getWidth() < o->getGame()->getWinWidth() / 2) {

			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() - 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				if(states[i].objectID == objectID)
					states[i].y = pos.getY() - 0.5;
			//o->setOriPos(pos);
			shop->setSP(states);
			//ultimaFilaY -= 20;
		}

		else if (x >= o->getGame()->getWinWidth() / 2 && pos.getX()  * o->getWidth() >= o->getGame()->getWinWidth() / 2) {

			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() - 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				if (states[i].objectID == objectID)
					states[i].y = pos.getY() - 0.5;
			//o->setOriPos(pos);
			shop->setSP(states);
			//ultimaFilaY -= 20;
		}
	}


	else if (event.wheel.y == -1) // scroll down
	{
		if (x < o->getGame()->getWinWidth() / 2 && pos.getX() * o->getWidth() < o->getGame()->getWinWidth() / 2) {
			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() + 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				if (states[i].objectID == objectID)
				states[i].y = pos.getY() + 0.5;
			//o->setOriPos(pos);
			shop->setSP(states);
			//ultimaFilaY += 20;
		}

		else if (x >= o->getGame()->getWinWidth() / 2 && pos.getX()  * o->getWidth() >= o->getGame()->getWinWidth() / 2) {

			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() + 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				if (states[i].objectID == objectID)
				states[i].y = pos.getY() + 0.5;
			//o->setOriPos(pos);
			shop->setSP(states);
			//ultimaFilaY -= 20;
		}
	}

	

	return handledEvent;
}
#include "MouseScrollComponent.h"
#include "ShopState.h"

MouseScrollComponent::MouseScrollComponent(ShopState* s)
{
	shop = s;
	
}


MouseScrollComponent::~MouseScrollComponent()
{
}

bool MouseScrollComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	states = shop->getSP();

	bool handledEvent = false;
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton
	Vector2D pos = o->getPosition();
	
	//handledEvent = (GameState::handleEvent(event));

	if (event.wheel.y == 1) // scroll up
		{
		if (x < o->getGame()->getWinWidth() / 2 && pos.getX()  * o->getWidth() < o->getGame()->getWinWidth() / 2) {

			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() - 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				states[i].y = pos.getY() - 0.5;
			shop->setSP(states);
			//ultimaFilaY -= 20;
		}

		else if (x >= o->getGame()->getWinWidth() / 2 && pos.getX()  * o->getWidth() >= o->getGame()->getWinWidth() / 2) {

			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() - 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				states[i].y = pos.getY() - 0.5;
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
				states[i].y = pos.getY() + 0.5;
			shop->setSP(states);
			//ultimaFilaY += 20;
		}

		else if (x >= o->getGame()->getWinWidth() / 2 && pos.getX()  * o->getWidth() >= o->getGame()->getWinWidth() / 2) {

			Vector2D pos = o->getPosition();
			pos.setY(pos.getY() + 0.5);
			o->setPosition(pos);
			for (int i = 0; i < states.size(); i++)
				states[i].y = pos.getY() + 0.5;
			shop->setSP(states);
			//ultimaFilaY -= 20;
		}
	}

	

	return handledEvent;
}
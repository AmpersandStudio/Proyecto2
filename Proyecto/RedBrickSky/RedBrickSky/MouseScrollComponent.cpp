#include "MouseScrollComponent.h"



MouseScrollComponent::MouseScrollComponent()
{
}


MouseScrollComponent::~MouseScrollComponent()
{
}

bool MouseScrollComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	

	bool handledEvent = false;
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton
	Vector2D pos = o->getPosition();

	if (event.wheel.y == 1) // scroll up
	{
		Vector2D pos = o->getPosition();
		pos.setY(pos.getY() - 0.5);
		o->setPosition(pos);
	}


	else if (event.wheel.y == -1) // scroll down
	{
		Vector2D pos = o->getPosition();
		pos.setY(pos.getY() + 0.5);
		o->setPosition(pos);
	}


	return handledEvent;
}

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
	

	if (event.wheel.y == 1) // scroll up
	{
		move(o, -1);
	}


	else if (event.wheel.y == -1) // scroll down
	{
		move(o);
	}


	return handledEvent;
}

void MouseScrollComponent::move(GameObject* o, int s) {

	Vector2D pos = o->getPosition();
	pos.setY(pos.getY() - 0.5 * s);
	o->setPosition(pos);
}
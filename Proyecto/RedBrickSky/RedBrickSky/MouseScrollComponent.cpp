#include "MouseScrollComponent.h"




MouseScrollComponent::MouseScrollComponent()
{
}


MouseScrollComponent::~MouseScrollComponent()
{
}

bool MouseScrollComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	
	//handledEvent = (GameState::handleEvent(event));

	if (event.wheel.y == 1) // scroll up
		{

		Vector2D pos = o->getPosition();
		pos.setY(pos.getY() - 0.5);
		o->setPosition(pos);
		//ultimaFilaY -= 20;

		}


	else if (event.wheel.y == -1) // scroll down
	{
		Vector2D pos = o->getPosition();
		pos.setY(pos.getY() + 0.5);
		o->setPosition(pos);
		//ultimaFilaY += 20;
	}

	return handledEvent;
}
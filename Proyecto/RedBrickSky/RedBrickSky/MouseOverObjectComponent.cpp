#include "MouseOverObjectComponent.h"



MouseOverObjectComponent::MouseOverObjectComponent()
{
	selected = false;
}


MouseOverObjectComponent::~MouseOverObjectComponent()
{
}

bool MouseOverObjectComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	
	 if (event.type == SDL_MOUSEMOTION) {
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos estado del raton

		Vector2D position = o->getPosition();

		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight())) {

			o->setColFrame(1);
		
			//SDL_SetTextureAlphaMod(o->getText()->getSDLText(), 100);
		}
		else {
			o->setColFrame(0);
		}
	}

	return handledEvent;
}

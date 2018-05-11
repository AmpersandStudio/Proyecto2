#include "MouseInfoClickComponent.h"
#include "ShopState.h"
#include "StringToScreen.h"


MouseInfoClickComponent::MouseInfoClickComponent(estado s, ShopState* shop) : shop_(shop)
{
	st = s;
	active_ = false;
}


MouseInfoClickComponent::~MouseInfoClickComponent()
{
}

bool MouseInfoClickComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_MOUSEMOTION) { //si es evento de raton
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos donde se ha producido el click

		Vector2D position = o->getPosition();

		//si el click es dentro de las dimensiones del boton
		if ((x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight()))) {
			active_ = true;

			StringToScreen::Instance()->setMessage("Nombre: " + st.nombre  + " ");
			StringToScreen::Instance()->setMessage("Precio: " + std::to_string(st.price)+ " ");
			StringToScreen::Instance()->startMessagin();
		
		}
	}

	else {
		active_ = false;
	}

	return handledEvent;
}
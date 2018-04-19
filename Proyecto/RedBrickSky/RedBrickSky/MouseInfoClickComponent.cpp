#include "MouseInfoClickComponent.h"
#include "ShopState.h"


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
	if (event.type == SDL_MOUSEBUTTONDOWN) { //si es evento de raton
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos donde se ha producido el click

		Vector2D position = o->getPosition();

		//si el click es dentro de las dimensiones del boton
		if (event.button.button == SDL_BUTTON_RIGHT && (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight()))) {
			active_ = true;

			shop_->setMessage("Nombre: " + st.nombre + "\n   Precio: " + std::to_string(st.price), x, y - 20);
			shop_->startMessagin();
		
		}
	}

	else if (event.type == SDL_MOUSEBUTTONUP) {
		active_ = false;
	}

	return handledEvent;
}
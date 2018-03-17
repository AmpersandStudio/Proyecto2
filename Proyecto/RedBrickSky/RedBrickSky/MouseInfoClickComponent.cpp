#include "MouseInfoClickComponent.h"



MouseInfoClickComponent::MouseInfoClickComponent(estado s)
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
			cout << "Informacion sobre el objeto:\n" << "   Nombre: " << st.nombre << "\n   Precio: " << st.price << endl;
		
		}
	}

	else if (event.type == SDL_MOUSEBUTTONUP) {
		active_ = false;
	}

	if(	active_)
		Game::Instance()->textPrinter("Hola", 50, 2, 2, Game::Instance()->getBlackColor());

	return handledEvent;
}
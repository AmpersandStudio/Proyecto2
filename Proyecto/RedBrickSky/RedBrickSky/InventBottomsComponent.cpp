#include "InventBottomsComponent.h"
#include "BackPack.h"



InventBottomsComponent::InventBottomsComponent(BackPack* b, vector<estado> v, bool vuelta)
{
	back = b;
	tipo = v;
	goingBack = vuelta;
}


InventBottomsComponent::~InventBottomsComponent()
{
}

bool InventBottomsComponent::handleEvent(GameObject* o, const SDL_Event& event) {

	bool handledEvent = false;
	Vector2D position = o->getPosition();
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT ) { //si es evento de raton

		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight())) {
			if (!goingBack) {
				back->elimina();
				back->creaSP();
				back->cargaElementos(tipo);
			}
			else {
				back->elimina();
				back->creaEscena();
			}
		}
	}

	return handledEvent;
}

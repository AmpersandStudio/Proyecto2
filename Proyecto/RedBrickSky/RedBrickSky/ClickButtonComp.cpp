#include "ClickButtonComp.h"
#include "Button.h"

ClickButtonComp::ClickButtonComp()
{
}

ClickButtonComp::~ClickButtonComp()
{
}

bool ClickButtonComp::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_MOUSEBUTTONDOWN) { //si es evento de raton
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos donde se ha producido el click

		Vector2D position = o->getPosition();

		//si el click es dentro de las dimensiones del boton
		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight())) {

			Button* b = dynamic_cast<Button*>(o);
			if (b != nullptr) {
				TheSoundManager::Instance()->playSound("click", 0);
				TheSoundManager::Instance()->playSound("select", 0);
				CallBackOnClick* cboc = b->getCallback();
				cboc(); //llamamos a la funcion callback generica que hemos pasado como parametro a la constructora
				handledEvent = true; //marcamos el evento como handleado
			}
		}
	}

	return handledEvent;
}

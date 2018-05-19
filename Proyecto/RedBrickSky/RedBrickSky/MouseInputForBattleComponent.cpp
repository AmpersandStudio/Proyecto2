#include "MouseInputForBattleComponent.h"
#include "Button.h"
#include "XboxController.h"

MouseInputForBattleComponent::MouseInputForBattleComponent(int a, int b) : a_(a), b_(b)
{
}

MouseInputForBattleComponent::~MouseInputForBattleComponent()
{
}

bool MouseInputForBattleComponent::handleEvent(GameObject* o, const SDL_Event& event) {
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
				handledEvent = true; //marcamos el evento como handleado
			}
		}
	}

	else if (event.type == SDL_JOYBUTTONDOWN) {
		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(a_, b_)) {
			handledEvent = true;
		}
		else if (event.type == SDL_JOYBUTTONUP) {
			XboxController::Instance()->onJoystickButtonUp(event);
		}
	}

	return handledEvent;
}
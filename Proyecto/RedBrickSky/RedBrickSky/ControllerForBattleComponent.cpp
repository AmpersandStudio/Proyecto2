#include "ControllerForBattleComponent.h"
#include "SoundManager.h"
#include "Button.h"
#include "checkML.h"
#include "XboxController.h"

ControllerForBattleComponent::ControllerForBattleComponent(int a, int b) : a_(a), b_(b)
{
}

ControllerForBattleComponent::~ControllerForBattleComponent()
{
}

bool ControllerForBattleComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_JOYBUTTONDOWN) { 
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
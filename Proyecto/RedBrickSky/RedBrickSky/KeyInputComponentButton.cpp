#include "KeyInputComponentButton.h"
#include "Button.h"


KeyInputComponentButton::KeyInputComponentButton(SDL_Keycode upLeft, SDL_Keycode downLeft, SDL_Keycode upRight, SDL_Keycode downRight, SDL_Keycode enter)
{
	upLeft_ = upLeft; downLeft_ = downLeft; upRight_ = upRight; downRight_ = downRight; enter_ = enter;
}


KeyInputComponentButton::~KeyInputComponentButton()
{
}

bool KeyInputComponentButton::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_KEYDOWN) {
		Button* b = dynamic_cast<Button*>(o);
		if (b != nullptr) {
			if (event.key.keysym.sym == upLeft_) {
				if (b->getFlag() == 0)
					b->actSelected();
				else
					b->enableSelected();
			}
			else if (event.key.keysym.sym == downLeft_) {
				if (b->getFlag() == 1)
					b->actSelected();
				else
					b->enableSelected();
			}
			else if (event.key.keysym.sym == upRight_) {
				if (b->getFlag() == 2)
					b->actSelected();
				else
					b->enableSelected();
			}
			else if (event.key.keysym.sym == downRight_) {
				if (b->getFlag() == 3)
					b->actSelected();
				else
					b->enableSelected();
			}
			else if (event.key.keysym.sym == enter_) {
				if (b->getSelected()) {
					CallBackOnClick* cboc = b->getCallback();
					cboc();
				}
			}
			//if (b->getSelected())
			//	SDL_SetTextureAlphaMod(o->getText()->getSDLText(), 100);
			//else
			//	SDL_SetTextureAlphaMod(o->getText()->getSDLText(), 255);
		}
	}

	return handledEvent;
}

#include "KeyInputComponent.h"


KeyInputComponent::KeyInputComponent(SDL_Keycode up, SDL_Keycode down, SDL_Keycode right, SDL_Keycode left, int rows, int cols)
{
	up_ = up; down_ = down; right_ = right; left_ = left; rows_ = rows; cols_ = cols;
}

KeyInputComponent::~KeyInputComponent()
{
}

bool KeyInputComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_KEYDOWN) {
		Vector2D position = o->getPosition();
		if (event.key.keysym.sym == up_) {
			double posY = position.getY();
			posY--;
			if (posY >= 0)
				position.setY(posY);
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == down_) {
			double posY = position.getY();
			posY++;
			if (posY < rows_)
				position.setY(posY);
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == right_) {
			double posX = position.getX();
			posX++;
			if (posX < cols_)
				position.setX(posX);
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == left_) {
			double posX = position.getX();
			posX--;
			if (posX >= 0)
				position.setX(posX);
			o->setPosition(position);
		}
	}
	return handledEvent;
}

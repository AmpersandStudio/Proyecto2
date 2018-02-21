#include "Button.h"

Button::Button(Game* gamePtr, CallBackOnClick* cb, int flag) : GameComponent (gamePtr)
{
	cboc_ = cb;
	flag_ = flag;
}

Button::~Button()
{
}

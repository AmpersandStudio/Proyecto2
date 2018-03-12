#include "Button.h"

Button::Button(CallBackOnClick* cb, int flag)
{
	cboc_ = cb;
	flag_ = flag;
}

Button::~Button()
{
}

#include "Button.h"

Button::Button(std::string id, CallBackOnClick* cb, int flag)
{
	cboc_ = cb;
	flag_ = flag;
	textureId_ = id;
}

Button::~Button()
{
}

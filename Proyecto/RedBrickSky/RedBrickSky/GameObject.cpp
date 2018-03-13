#include "GameObject.h"

GameObject::GameObject()
{
	position_ = Vector2D(0, 0);
	iniPosition_ = Vector2D(0, 0);
	direction_ = Vector2D(0, 0);
	width_ = 0;
	height_ = 0;
	colFrame_ = 0;
	rowFrame_ = 0;
	numFrames_ = 0;
	animSpeed_ = 0;
	alpha_ = 255;
	angle_ = 0;
	callbackId_ = 0;
}

GameObject::~GameObject()
{
}

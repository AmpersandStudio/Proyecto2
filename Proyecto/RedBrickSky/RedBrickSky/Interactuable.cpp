#include "Interactuable.h"
#include "TextureManager.h"
#include "StateMachine.h"
#include "ShopState.h"

Interactuable::Interactuable()
{
}

Interactuable::~Interactuable()
{
	clean();
}

void Interactuable::load(Vector2D position, int width, int height, std::string id, int numFrames, int callbackID, int animSpeed)
{
	setPosition(position);
	setWidth(width);
	setHeight(height);
	setTextureId(id);
	setNumFrames(numFrames);
	setCallbackId(callbackID);
	animSpeed_ = animSpeed;

	generateCollider();
}

bool Interactuable::handleEvent(const SDL_Event& event)
{
	return false;
}

void Interactuable::update()
{
	return;
}

void Interactuable::render()
{
	TextureManager::Instance()->drawFrame(textureId_, (Uint32)position_.getX(), (Uint32)position_.getY(),
		width_, height_, rowFrame_, colFrame_, TheGame::Instance()->getRenderer(), angle_, alpha_);
}

void Interactuable::clean()
{
	return;
}

void Interactuable::activate()
{
	std::cout << "Elemento interactuado." << std::endl;
	TheGame::Instance()->getStateMachine()->pushState(new ShopState());
}

void Interactuable::generateCollider()
{
	collider_.x = position_.getX();
	collider_.y = position_.getY();
	collider_.w = width_;
	collider_.h = height_;
}

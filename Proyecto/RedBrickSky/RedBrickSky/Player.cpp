#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "StateMachine.h"

Player::Player()
{

}

Player::~Player()
{
}

void Player::load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed)
{
	position_ = position;
	width_ = width;
	height_ = height;
	textureId_ = textureId;
	numFrames_ = numFrames;
	callbackId_ = callbackID;
	animSpeed_ = animSpeed;

	direction_ = Vector2D(0, -1);
	m_moveSpeed = 10;
	interacting_ = false;
	updateRect();
}

void Player::render()
{
	TextureManager::Instance()->drawFrame(textureId_, (Uint32)position_.getX(), (Uint32)position_.getY(),
		width_, height_, rowFrame_, colFrame_, TheGame::Instance()->getRenderer(), angle_, alpha_);
}

void Player::update()
{
	// refresh position
	position_ = position_ + velocity_;

	// refresh animation frame
	handleAnimation();
}

bool Player::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			velocity_.set(Vector2D(-m_moveSpeed, 0));
			direction_.set(-1, 0);
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			velocity_.set(Vector2D(m_moveSpeed, 0));
			direction_.set(1, 0);
		}
		if (event.key.keysym.sym == SDLK_UP)
		{
			velocity_.set(Vector2D(0, -m_moveSpeed));
			direction_.set(0, -1);
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			velocity_.set(Vector2D(0, m_moveSpeed));
			direction_.set(0, 1);
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Game::Instance()->getStateMachine()->popState();
		}
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			updateRect();
			SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &actionRect_);
			SDL_RenderPresent(TheGame::Instance()->getRenderer());
			setInteracting(true);
		}
		if (event.key.keysym.sym == SDLK_f)
		{
			int flags = SDL_GetWindowFlags(TheGame::Instance()->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), 0);
			else SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), SDL_WINDOW_FULLSCREEN);
		}
		return true;
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_UP:
		case SDLK_DOWN:
			std::cout << "KEYUP" << std::endl;
			velocity_ = Vector2D(0, 0);
			break;

		default:
			break;
		}
	}
	else if (event.type == SDL_QUIT) 
	{
		Game::Instance()->exitApp();
		return true;
	}

	return false;
}

void Player::collision()
{
	velocity_ = Vector2D(0, 0);
}

void Player::handleAnimation()
{
	colFrame_ = int(((SDL_GetTicks() / (100)) % numFrames_));
}

void Player::updateRect()
{
	if (direction_.getX() == -1 && direction_.getY() == 0)
	{
		actionRect_ = { (int)(position_.getX() - width_), (int)position_.getY(), (int)width_, (int)height_ };
	}
	else if (direction_.getX() == 1 && direction_.getY() == 0)
	{
		actionRect_ = { (int)(position_.getX() + width_), (int)position_.getY(), (int)width_, (int)height_ };
	}
	else if (direction_.getX() == 0 && direction_.getY() == -1)
	{
		actionRect_ = { (int)position_.getX(), (int)(position_.getY() - height_), (int)width_, (int)height_ };
	}
	else if (direction_.getX() == 0 && direction_.getY() == 1)
	{
		actionRect_ = { (int)position_.getX(), (int)(position_.getY() + height_), (int)width_, (int)height_ };
	}
}


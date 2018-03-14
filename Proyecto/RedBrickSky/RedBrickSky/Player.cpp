#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "StateMachine.h"
#include "PauseState.h"
#include "BackPack.h"
#include "Dialogue.h"

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
			Game::Instance()->getStateMachine()->pushState(new PauseState());
		}
		if (event.key.keysym.sym == SDLK_i)
		{
			Game::Instance()->getStateMachine()->pushState(new BackPack());
		}
		if (event.key.keysym.sym == SDLK_t)
		{
			int level_dialogues = 1;
			Dialogue d = Dialogue(level_dialogues);
			Game::Instance()->textPrinter(d.getText('E', 1), 200, Game::Instance()->getWinWidth() / 3, Game::Instance()->getWinHeight() / 2, Game::Instance()->getBlackColor());
		}
		if (event.key.keysym.sym == SDLK_SPACE)	// interactuar
		{
			updateRect();
			SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &actionRect_);
			SDL_RenderPresent(TheGame::Instance()->getRenderer());
			setInteracting(true);
		}
		if (event.key.keysym.sym == SDLK_f)	// fullscreen mode
		{
			// Comentando para que los PC dirty peasant no se rompan
			//int flags = SDL_GetWindowFlags(TheGame::Instance()->getWindow());
			//if (flags & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), 0);
			//else SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), SDL_WINDOW_FULLSCREEN);
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


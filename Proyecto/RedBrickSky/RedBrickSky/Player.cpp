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

	m_moveSpeed = 10;
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
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			velocity_.set(Vector2D(m_moveSpeed, 0));
		}
		if (event.key.keysym.sym == SDLK_UP)
		{
			velocity_.set(Vector2D(0, -m_moveSpeed));
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			velocity_.set(Vector2D(0, m_moveSpeed));
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Game::Instance()->getStateMachine()->popState();
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
	//position_ = position_ - velocity_;
	velocity_ = Vector2D(0, 0);
}

void Player::handleAnimation()
{
	colFrame_ = int(((SDL_GetTicks() / (100)) % numFrames_));
}

	// FUNCIONALIDAD INTERACTUAR
	// Debemos crear una clase Interactuable que herede de GameObject (volvemos a tener el problema de
	// la GameObjectFactory). Esta clase es abstracta, y sólo contiene un método virtual void Activate();
	// cada GO creado con este tipo implementa un Activate diferente en función de lo que queramos que haga
	// (mostrar un cuadro de diálogo, comenzar una batalla, añadir un item, etc.)
	// Al parsear el nivel (LevelParser) si detectamos uno de estos objetos (parseObjectLayers) debemos
	// añadirlo a un vector de Interactuable* (en Level). 
	// Al pulsar SPACE se genera un rectangulo en la dirección que mire el personaje:
	// case (0, -1): SDL_Rect int_rect RECT(position_.getX(), position_.getY() - height_, width_, height_);
	// case (1, 0): SDL_Rect int_rect RECT(position_.getX() + width_, position_.getY(), width_, height_);
	// case (0, 1): SDL_Rect int_rect RECT(position_.getX(), position_.getY() + height_, width_, height_);
	// case (-1, 0): SDL_Rect int_rect RECT(position_.getX() - width_, position_.getY(), width_, height_);
	// Después, llamamos a un metodo CheckInteraction(), que recorre el vector<Interactuable*> de Level.
	// Para cada GO Interactuable, se genera un SDL_Rect y se comprueba si está colisionando con el SDL_Rect
	// creado por el jugador. Si se produce una colisión, se toma el GO correspondiente y se llama a su
	// metodo Activate (en cada iteracion hay que hacer delete del SDL_Rect creado para cada Interactuable).


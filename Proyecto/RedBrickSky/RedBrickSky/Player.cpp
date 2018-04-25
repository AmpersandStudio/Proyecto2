#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "StateMachine.h"
#include "PauseState.h"
#include "BackPack.h"
#include "Camera.h"



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
	m_moveSpeed = 4;
	interacting_ = false;
	running_ = false;
	text = false;
	previousPos_ = iniPosition_;
	updateRect();


	d_ = Dialogue("NPC1");
	d_.update();

	TheCamera::Instance()->setTarget(&position_);

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();
}

void Player::render()
{
	//SDL_Rect fillRect = { (Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX() , (Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(), width_, height_ };
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0x00, 0xFF, 0xFF);
	//SDL_RenderFillRect(Game::Instance()->getRenderer(), &fillRect);

	TextureManager::Instance()->drawFrame(textureId_,
		(Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX(),
		(Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(),
		width_, height_, rowFrame_, colFrame_, TheGame::Instance()->getRenderer(), angle_, alpha_);

	//SDL_Rect fillRect2 = { (Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX() - width_,
	//	(Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY() - height_,
	//	3 * width_, 3 * height_ };
	//SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	//SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &fillRect2);

	if (text)
	{
		d_.render();
	}
}

void Player::update()
{
	moved_ = false; // En el update determinamos que el jugador no se mueve y solo cambiará si se produce un evento


	if (!GameManager::Instance()->getDialogueState()) { //Para evitar que se mueva si otro NPC le empuja al hablar, lo cual bloquearía el juego
		position_ = position_ + velocity_; // refresh position
	}

	if (previousPos_.getX() != position_.getX() || previousPos_.getY() != position_.getY()) {
		TheCamera::Instance()->setTarget(&position_);
		moved_ = true;
	}

	previousPos_ = position_;
	// refresh animation frame
	handleAnimation();

	if (text) {
		d_.setX(position_.getX());
		d_.setY(position_.getY());
		if (!d_.isActive()) {
			d_.update();
		}
	}
}

bool Player::handleEvent(const SDL_Event& event)
{

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		if (!GameManager::Instance()->getDialogueState())
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
			if (event.key.keysym.sym == SDLK_r)
			{
				m_moveSpeed = (running_) ? 10 : 20;
				running_ = !running_;
			}
			if (event.key.keysym.sym == SDLK_i)
			{
				Game::Instance()->getStateMachine()->pushState(new BackPack());
			}
		}

		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Game::Instance()->getStateMachine()->pushState(new PauseState());
		}

		if (event.key.keysym.sym == SDLK_SPACE)	// interactuar
		{
			updateRect();
			interacting();
		}
		if (event.key.keysym.sym == SDLK_f)	// fullscreen mode
		{
			// Comentando para que los PC dirty peasant no se rompan
			int flags = SDL_GetWindowFlags(TheGame::Instance()->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), 0);
			else SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), SDL_WINDOW_FULLSCREEN);
		}
		if (event.key.keysym.sym == SDLK_t)
		{
			if (!text) {
				text = true;
			}
			else {
				text = d_.nextDialogue();
			}
		}
		return true;
	}

	else if (XboxController::Instance()->getNumControllers() > 0) { //Primero comprobamos si hay algún mando conectado
																	//CONTROLAR LOS INPUTS MEDIANTE MANDO DE LA XBOX360
		if (event.type == SDL_JOYAXISMOTION) {
			XboxController::Instance()->onJoystickAxisMove(event);

			if (XboxController::Instance()->xvalue(0, 1) < 0)
			{
				velocity_.set(Vector2D(-m_moveSpeed, 0));
				direction_.set(-1, 0);

			}
			else if (XboxController::Instance()->xvalue(0, 1) > 0)
			{
				velocity_.set(Vector2D(m_moveSpeed, 0));
				direction_.set(1, 0);

			}
			else if (XboxController::Instance()->yvalue(0, 1) < 0)
			{
				velocity_.set(Vector2D(0, -m_moveSpeed));
				direction_.set(0, -1);

			}
			else if (XboxController::Instance()->yvalue(0, 1) > 0)
			{
				velocity_.set(Vector2D(0, m_moveSpeed));
				direction_.set(0, 1);

			}
			else {
				velocity_.set(Vector2D(0, 0));
				direction_.set(0, 0);

			}

		}
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
			XboxController::Instance()->onJoystickButtonDown(event);

			if (XboxController::Instance()->getButtonState(0, 7)) //botón de pausa
			{
				Game::Instance()->getStateMachine()->pushState(new PauseState());
			}
			if (XboxController::Instance()->getButtonState(0, 6)) //botón de back
			{
				Game::Instance()->getStateMachine()->pushState(new BackPack());
			}

			if (XboxController::Instance()->getButtonState(0, 0))	// Botón A
			{
				interacting();
			}
			XboxController::Instance()->onJoystickButtonUp(event); //Aseguro que levantamos el botón después de usarlo
		}
		if (event.type == SDL_JOYBUTTONUP)
			XboxController::Instance()->onJoystickButtonUp(event);
	}
	//TERMINAMOS DE COMPROBAR CON EL MANDO DE LA XBOX

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

void Player::interacting() {
	std::cout << "Interacting...\n";
	updateRect();

	setInteracting(true);
}

void Player::collision()
{
	velocity_ = Vector2D(0, 0);
}

void Player::handleAnimation()
{
	if (velocity_.getX() == 0 && velocity_.getY() == 0)
	{
		colFrame_ = 1;
	}
	else
	{
		if (velocity_.getY() < 0)
		{
			rowFrame_ = 3;
		}
		else if (velocity_.getY() > 0)
		{
			rowFrame_ = 0;
		}
		else if (velocity_.getY() == 0)
		{
			rowFrame_ = (velocity_.getX() < 0) ? 1 : 2;
		}
		colFrame_ = int(((SDL_GetTicks() / (100)) % numFrames_));
	}

}

void Player::updateRect()
{
	/*if (direction_.getX() == -1 && direction_.getY() == 0)
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
	}*/

	actionRect_ = { (int)(position_.getX() - width_), (int)(position_.getY() - height_), 3 * (int)width_, 3 * (int)height_ };
}
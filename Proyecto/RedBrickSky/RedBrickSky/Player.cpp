#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "StateMachine.h"
#include "PauseState.h"
#include "BackPack.h"
#include "Dialogue.h"
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
	m_moveSpeed = 10;
	interacting_ = false;
	running_ = false;
	updateRect();

	TheCamera::Instance()->setTarget(&position_);
	initialiseJoysticks();

}

void Player::render()
{
	TextureManager::Instance()->drawFrame(textureId_, 
		(Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX(), 
		(Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(),
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
		if (event.key.keysym.sym == SDLK_r)
		{
			m_moveSpeed = (running_) ? 10 : 20;
			running_ = !running_;
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
			//Game::Instance()->textPrinter(d.getText('E', 1), 200, Game::Instance()->getWinWidth() / 3, Game::Instance()->getWinHeight() / 2, Game::Instance()->getBlackColor());
			Game::Instance()->textPrinter(d.getText('E', 1), 200, 2, 2, Game::Instance()->getBlackColor()); //El problema del anterior es que se pinta fuera de pantalla
		}
		if (event.key.keysym.sym == SDLK_SPACE)	// interactuar
		{
			interacting();
		}
		if (event.key.keysym.sym == SDLK_f)	// fullscreen mode
		{
			// Comentando para que los PC dirty peasant no se rompan
			/*int flags = SDL_GetWindowFlags(TheGame::Instance()->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), 0);
			else SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), SDL_WINDOW_FULLSCREEN);*/
		}
		return true;
	}

	//CONTROLAR LOS INPUTS MEDIANTE MANDO DE LA XBOX360
	else if (event.type == SDL_JOYAXISMOTION) {
		onJoystickAxisMove(event);

		if (xvalue(0, 1) < 0)
		{
			velocity_.set(Vector2D(-m_moveSpeed, 0));
			direction_.set(-1, 0);
		}
		else if (xvalue(0,1) > 0)
		{
			velocity_.set(Vector2D(m_moveSpeed, 0));
			direction_.set(1, 0);
		}
		else if (yvalue(0, 1) < 0)
		{
			velocity_.set(Vector2D(0, -m_moveSpeed));
			direction_.set(0, -1);
		}
		else if (yvalue(0, 1) > 0)
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
		onJoystickButtonDown(event);

		if (getButtonState(0, 7)) //botón de pausa
		{
			Game::Instance()->getStateMachine()->pushState(new PauseState());
		}
		if (getButtonState(0, 6)) //botón de back
		{
			Game::Instance()->getStateMachine()->pushState(new BackPack());
		}

		if (getButtonState(0, 0))	// Botón A
		{
			interacting();
		}
		onJoystickButtonUp(event); //Aseguro que levantamos el botón después de usarlo
	}
	if (event.type == SDL_JOYBUTTONUP)
		onJoystickButtonUp(event);

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
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &actionRect_);
	SDL_RenderPresent(TheGame::Instance()->getRenderer());
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


//METODOS PARA EL MANDO DE LA XBOX360

void Player::onJoystickButtonDown(SDL_Event event)
{
	int whichOne = event.jaxis.which;
	std::cout << event.jaxis.which << endl;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void Player::onJoystickButtonUp(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void Player::initialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		for (size_t i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (joy != NULL)
			{
				m_joysticks.push_back(joy);

				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));

				std::vector<bool> tempButtons;

				for (size_t j = 0; j < SDL_JoystickNumButtons(joy); ++j)
				{
					tempButtons.push_back(false);
				}

				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				std::cout << "Joystick load fail! SDL Error: " << SDL_GetError() << "\n";
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << " joystick(s)\n";
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

int Player::xvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getX();
		}
	}
	return 0;
}

int Player::yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}

void Player::onJoystickAxisMove(SDL_Event event)
{
	int whichOne = event.jaxis.which;

	//Left Stick: left / right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}

	//Left Stick: up / down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}

	//Right Stick: left / right
	if (event.jaxis.axis == 2)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}

	//Right Stick: up / down
	if (event.jaxis.axis == 5)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}
}
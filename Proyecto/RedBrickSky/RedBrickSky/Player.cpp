#include "Player.h"
#include "TextureManager.h"
#include "Game.h"

Player::Player(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed) : GameObject()
{
	position_ = position;
	width_ = width;
	height_ = height;
	textureId_ = textureId;
	numFrames_ = numFrames;
	callbackId_ = callbackID;
	animSpeed_ = animSpeed;
}

Player::~Player()
{
}

void Player::render()
{
	TextureManager::Instance()->drawFrame(textureId_, (Uint32)position_.getX(), (Uint32)position_.getY(),
		width_, height_, rowFrame_, colFrame_, TheGame::Instance()->getRenderer(), angle_, alpha_);
}

void Player::update()
{
	// reset velocity
	velocity_ = Vector2D(0, 0);

	// handle input
	handleInput();

	// refresh position
	position_ = position_ + velocity_;

	// refresh animation frame
	handleAnimation();
}

bool Player::handleEvent(const SDL_Event& event)
{
	return false;
}

void Player::collision()
{
	position_ = position_ - velocity_;
}

void Player::handleAnimation()
{
	colFrame_ = int(((SDL_GetTicks() / (100)) % numFrames_));
}

void Player::handleInput()
{
	// NCM: hay que introducir el InputHandler para utilizar este metodo.
	// No hay que confundirlo con handleEvents, ya que de implementar el
	// mencionado InputHandler, este seria el �nico en gestionar dicho
	// metodo. Para cada estado / objeto tendriamos un handleInput llamado
	// desde el update que utilizaria los recursos de InputHandler y su
	// handleEvents (que se llamaria desde el bucle principal en Game)

	// FUNCIONALIDAD INTERACTUAR
	// Debemos crear una clase Interactuable que herede de GameObject (volvemos a tener el problema de
	// la GameObjectFactory). Esta clase es abstracta, y s�lo contiene un m�todo virtual void Activate();
	// cada GO creado con este tipo implementa un Activate diferente en funci�n de lo que queramos que haga
	// (mostrar un cuadro de di�logo, comenzar una batalla, a�adir un item, etc.)
	// Al parsear el nivel (LevelParser) si detectamos uno de estos objetos (parseObjectLayers) debemos
	// a�adirlo a un vector de Interactuable* (en Level). 
	// Al pulsar SPACE se genera un rectangulo en la direcci�n que mire el personaje:
	// case (0, -1): SDL_Rect int_rect RECT(position_.getX(), position_.getY() - height_, width_, height_);
	// case (1, 0): SDL_Rect int_rect RECT(position_.getX() + width_, position_.getY(), width_, height_);
	// case (0, 1): SDL_Rect int_rect RECT(position_.getX(), position_.getY() + height_, width_, height_);
	// case (-1, 0): SDL_Rect int_rect RECT(position_.getX() - width_, position_.getY(), width_, height_);
	// Despu�s, llamamos a un metodo CheckInteraction(), que recorre el vector<Interactuable*> de Level.
	// Para cada GO Interactuable, se genera un SDL_Rect y se comprueba si est� colisionando con el SDL_Rect
	// creado por el jugador. Si se produce una colisi�n, se toma el GO correspondiente y se llama a su
	// metodo Activate (en cada iteracion hay que hacer delete del SDL_Rect creado para cada Interactuable).
}

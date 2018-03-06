#include "PlayState.h"

//Includes para el boton de la tienda
#include "Button.h"
#include "StateMachine.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"
#include "MovementInputComponent.h"
#include "ShopState.h"
#include "BattleState.h"
#include "BackPack.h"
#include "TransitionState.h"

#include "PauseState.h"

PlayState::PlayState(Game* gamePtr) : GameState (gamePtr)
{
	//ESTO ES DE JAVI, UN BOTON QUE TE LLEVA A LA TIENDA DESDE DENTRO DEL JUEGO PORQUE GAME STATE ES EL QUE TIENE LA INFO DE LA MOCHILA,
	//MODIFICAD LA POSICION SI QUEREIS PERO DECIDMELO PLS

	Button* button0 = new Button(gamePtr, toGame, 0);
	Texture* tx0 = gamePtr->getTexture(2);
	Vector2D position0(5, 6);
	double width = 150;
	double height = 100;
	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic2 = new MouseInputComponentButton();
	button0->setText(tx0); button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic2);

	stage.push_back(button0);

	Button* button1 = new Button(gamePtr, toInventary, 1);

	Texture* tx1 = gamePtr->getTexture(1);

	Vector2D position1(7, 6);

	button1->setText(tx1); button1->setPosition(position1); button1->setWidth(width); button1->setHeight(height); button1->addRenderComponent(rc); button1->addInputComponent(ic2);
	
	stage.push_back(button1);

	//ESTO ES DE MARTIN, UN BOTON PARA IR AL BATTLESTATE
	Button* button2 = new Button(gamePtr, toBattle, 2);
	Texture* tx2 = gamePtr->getTexture(18);
	Vector2D position2(3, 6);
	button2->setText(tx2); button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic2);
	stage.push_back(button2);


	initPlayer();

}

PlayState::~PlayState()
{
}

// Input general del estado: acceso a menús e input de los objetos del estado
bool PlayState::handleEvent(SDL_Event & event)
{

	// 1) Comprueba las teclas de acceso a los distintos menús, etc.
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			game_->getStateMachine()->pushState(new PauseState(game_));
		else if (event.key.keysym.sym == SDLK_i)
			game_->getStateMachine()->pushState(new BackPack(game_));
	}
	// 2) LLama a los input de cada objeto del propio estado
	return GameState::handleEvent(event);
}

//PARA JAVI PROBAR LA TIENDA TAMBIEN
void PlayState::toGame(Game* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new ShopState(game));
}

//PARA JAVI PROBAR LA TIENDA TAMBIEN
void PlayState::toInventary(Game* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new BackPack(game));
}

void PlayState::initPlayer()
{
	player_ = new GameComponent(game_);

	InputComponent* movementComp = new MovementInputComponent(SDLK_w, SDLK_s, SDLK_a, SDLK_d) ; // Para el jugador
	RenderComponent* rc = new RenderFrameComponent(); // AVISO: CON ESTE NO SE VE EL MOVIMIENTO
	
	player_->addInputComponent(movementComp);
	player_->addRenderComponent(rc);


	// Para probar
	Texture* testTex = game_->getTexture(4);
	player_->setText(testTex);
	player_->setWidth(70); player_->setHeight(70);
	player_->setPosition(Vector2D(6, 6));

	stage.push_back(player_);
	
}

//DE MARTIN PARA PROBAR BATTLESTATE
void PlayState::toBattle(Game* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new TransitionState(game));
}


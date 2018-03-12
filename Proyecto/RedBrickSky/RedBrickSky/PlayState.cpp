#include "PlayState.h"

//Includes para el boton de la tienda
#include "Button.h"
#include "StateMachine.h"
#include "KeyInputComponentButton.h"
#include "KeyInputComponent.h"
#include "MouseInputComponentButton.h"
#include "MovementInputComponent.h"
#include "ShopState.h"
#include "BattleState.h"
#include "BackPack.h"
#include "TransitionState.h"
#include "RenderFrameNDComponent.h"

#include "PauseState.h"
#include "MapState.h"

//Para probar lo de los dialogos
#include "Dialogue.h"

PlayState::PlayState()
{
	//ESTO ES DE JAVI, UN BOTON QUE TE LLEVA A LA TIENDA DESDE DENTRO DEL JUEGO PORQUE GAME STATE ES EL QUE TIENE LA INFO DE LA MOCHILA,
	//MODIFICAD LA POSICION SI QUEREIS PERO DECIDMELO PLS

	Button* button0 = new Button(toGame, 0);
	Texture* tx0 = Game::Instance()->getTexture(2);
	Vector2D position0(5, 6);
	double width = 150;
	double height = 100;
	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic2 = new MouseInputComponentButton();
	button0->setText(tx0); button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic2);

	stage.push_back(button0);

	Button* button1 = new Button(toInventary, 1);

	Texture* tx1 = Game::Instance()->getTexture(1);

	Vector2D position1(7, 6);

	button1->setText(tx1); button1->setPosition(position1); button1->setWidth(width); button1->setHeight(height); button1->addRenderComponent(rc); button1->addInputComponent(ic2);
	
	stage.push_back(button1);

	//ESTO ES DE MARTIN, UN BOTON PARA IR AL BATTLESTATE
	Button* button2 = new Button(toBattle, 2);
	Texture* tx2 = Game::Instance()->getTexture(18);
	Vector2D position2(3, 6);
	button2->setText(tx2); button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic2);
	stage.push_back(button2);

	Button* button3 = new Button(toMap, 3);
	Vector2D position3(1, 6);
	button3->setText(tx2); button3->setPosition(position3); button3->setWidth(width); button3->setHeight(height); button3->addRenderComponent(rc); button3->addInputComponent(ic2);
	stage.push_back(button3);

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
			Game::Instance()->getStateMachine()->pushState(new PauseState());
		else if (event.key.keysym.sym == SDLK_i)
			Game::Instance()->getStateMachine()->pushState(new BackPack());

		//CERDADA PARA PROBAR LA CLASE DE TEXTOS
		else if (event.key.keysym.sym == SDLK_t)
			{
				int level_dialogues = 1;
				Dialogue d = Dialogue(level_dialogues);
				Game::Instance()->textPrinter(d.getText('E', 1), 200, Game::Instance()->getWinWidth() / 3, Game::Instance()->getWinHeight() / 2, Game::Instance()->getBlackColor());
			}
	}
	// 2) LLama a los input de cada objeto del propio estado
	return GameState::handleEvent(event);
}

//PARA JAVI PROBAR LA TIENDA TAMBIEN
void PlayState::toGame() {
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new ShopState());
}

//PARA JAVI PROBAR LA TIENDA TAMBIEN
void PlayState::toInventary() {
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new BackPack());
}

void PlayState::initPlayer()
{
	player_ = new GameComponent();

	InputComponent* movementComp = new MovementInputComponent(SDLK_w, SDLK_s, SDLK_a, SDLK_d) ; // Para el jugador
	RenderComponent* rc = new RenderFrameNDComponent(); // AVISO: CON ESTE NO SE VE EL MOVIMIENTO

	//DE PABLO PARA PROBAR DIALOGOS
	KeyInputComponent* KeyComponent = new KeyInputComponent(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	
	player_->addInputComponent(movementComp);
	player_->addRenderComponent(rc);


	// Para probar
	Texture* testTex = Game::Instance()->getTexture(4);
	player_->setText(testTex);
	player_->setWidth(70); player_->setHeight(70);
	player_->setPosition(Vector2D(0, 0));
	player_->setVel(Vector2D(5, 5));

	stage.push_back(player_);
	
}

//DE MARTIN PARA PROBAR BATTLESTATE
void PlayState::toBattle() {
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new TransitionState());
}

void PlayState::toMap()
{
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new MapState());
}



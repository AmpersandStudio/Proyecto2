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

//Para probar lo de los dialogos
#include "Dialogue.h"

PlayState::PlayState()
{
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/provisionalTutorial.tmx");

	//ESTO ES DE JAVI, UN BOTON QUE TE LLEVA A LA TIENDA DESDE DENTRO DEL JUEGO PORQUE GAME STATE ES EL QUE TIENE LA INFO DE LA MOCHILA,
	//MODIFICAD LA POSICION SI QUEREIS PERO DECIDMELO PLS

	//Button* button0 = new Button("2", toGame, 0);
	//Vector2D position0(5, 6);
	double width = 150;
	double height = 100;
	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic2 = new MouseInputComponentButton();
	//button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic2);

	//stage.push_back(button0);

	//Button* button1 = new Button("1", toInventary, 1);
	//Vector2D position1(7, 6);
	//button1->setPosition(position1); button1->setWidth(width); button1->setHeight(height); button1->addRenderComponent(rc); button1->addInputComponent(ic2);
	//
	//stage.push_back(button1);

	//ESTO ES DE MARTIN, UN BOTON PARA IR AL BATTLESTATE
	Button* button2 = new Button("18", toBattle, 2);
	Vector2D position2(7, 6);
	button2->setPosition(position2); button2->setWidth(width); button2->setHeight(height); button2->addRenderComponent(rc); button2->addInputComponent(ic2);
	stage.push_back(button2);

	//initPlayer();

	//TheSoundManager::Instance()->playMusic("music", 0);
}

PlayState::~PlayState()
{
	delete pLevel;
}

// Input general del estado: acceso a menús e input de los objetos del estado
bool PlayState::handleEvent(const SDL_Event & event)
{
	if (pLevel->getPlayer()->handleEvent(event)) return true;

	return GameState::handleEvent(event);
}

void PlayState::update()
{
	pLevel->update();
	GameState::update();
}

void PlayState::render()
{
	pLevel->render();
	GameState::render();
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

//void PlayState::initPlayer()
//{
//	player_ = new GameComponent();
//
//	InputComponent* movementComp = new MovementInputComponent(SDLK_w, SDLK_s, SDLK_a, SDLK_d) ; // Para el jugador
//	RenderComponent* rc = new RenderFrameComponent(); // AVISO: CON ESTE NO SE VE EL MOVIMIENTO
//
//	//DE PABLO PARA PROBAR DIALOGOS
//	KeyInputComponent* KeyComponent = new KeyInputComponent(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
//	
//	player_->addInputComponent(movementComp);
//	player_->addRenderComponent(rc);
//
//
//	// Para probar
//	player_->setTextureId("4");
//	player_->setWidth(70); player_->setHeight(70);
//	player_->setPosition(Vector2D(0, 0));
//	player_->setVel(Vector2D(5, 5));
//
//	stage.push_back(player_);
//	
//}

//DE MARTIN PARA PROBAR BATTLESTATE
void PlayState::toBattle() {
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->pushState(new TransitionState());
}



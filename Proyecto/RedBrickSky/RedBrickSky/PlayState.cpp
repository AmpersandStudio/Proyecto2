#include "PlayState.h"

//Includes para el boton de la tienda
#include "Button.h"
#include "StateMachine.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"
#include "ShopState.h"

PlayState::PlayState(Game* gamePtr) : GameState (gamePtr)
{
	//ESTO ES DE JAVI, UN BOTON QUE TE LLEVA A LA TIENDA DESDE DENTRO DEL JUEGO PORQUE GAME STATE ES EL QUE TIENE LA INFO DE LA MOCHILA,
	//MODIFICAD LA POSICION SI QUEREIS PERO DECIDMELO PLS

	Button* button0 = new Button(gamePtr, toGame, 0);
	Texture* tx0 = gamePtr->getTexture(2);
	Vector2D position0(6, 6);
	double width = 150;
	double height = 100;
	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic2 = new MouseInputComponentButton();
	button0->setText(tx0); button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(rc); button0->addInputComponent(ic2);

	stage.push_back(button0);

}

PlayState::~PlayState()
{
}

//PARA JAVI PROBAR LA TIENDA TAMBIEN
void PlayState::toGame(Game* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new ShopState(game));
}
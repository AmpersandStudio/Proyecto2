#include "ShopState.h"
#include "Button.h"
#include "Item.h"

ShopState::ShopState(Game* gamePtr) : GameState (gamePtr)
{
	game = gamePtr; //Puntero al juego


}

ShopState::~ShopState()
{
}

bool ShopState::handleEvent(SDL_Event& event) {

	bool handledEvent = false;
	
	return handledEvent;
}

void ShopState::render() {

	

}

void ShopState::cambiaDinero(int n) {

	dinero = dinero - n;
}

bool ShopState::devMat(int& x, int& y, int ident, Item* elemento) {
	bool aceptada = false;
	return aceptada;
}

void ShopState::mouseEncima(int x, int y) {

	
}

void ShopState::vuelveNormal() {

	
}

void ShopState::creaFila() {

}

void ShopState::toMenu(Game* game) {

	
}
#include "Item.h"



Item::Item(ShopState* shop,Game* gamePtr, Texture* t, int x, int y, int w, int h, int p, bool s, int matX, int matY, int idem) : GameObject(gamePtr)
{
	isMouseSelection = false;
	posX = x; posY = y;
	oriX = x; oriY = y;
	width = w; heigth = h;
	textptr = t;
	precio = p;
	comprado = false;
	SP = s;
	mX = matX;
	mY = matY;
	identificador = idem;
	frame = 0;
	shop_ = shop;
}


Item::~Item()
{
}

void Item::render() {

}

bool Item::handleEvent(SDL_Event& event) {

	bool handledEvent = false;
	
	return handledEvent;
}


void Item::cambiaSprite(int x) {
	frame = x;
}

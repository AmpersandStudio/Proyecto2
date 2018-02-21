#pragma once
#include "GameObject.h"
#include "ShopState.h"
class Item :
	public GameObject
{
private:
	bool isMouseSelection;
	int posX, posY;
	int width, heigth; int oriX, oriY;
	int precio;
	bool comprado;
	bool SP;
	int mX, mY;
	int frame;
	Texture* textptr;
	ShopState* shop_;
	int identificador;

public:
	Item(ShopState* shop ,Game* gamePtr, Texture* t, int x, int y, int w, int h, int p, bool s, int matX, int matY, int idem);
	virtual ~Item();
	virtual bool handleEvent(SDL_Event& event);
	virtual void render();
	virtual void update() {};
	int getX() { return posX; };
	int getY() { return posY; };
	int getH() { return heigth; };
	int getW() { return width; };
	void setX(int x) { posX = x; };
	void setY(int y) { posY = y; };
	int getmX() { return mX; };
	int getmY() { return mY; };
	int getIdentificador() { return identificador; };
	bool getSP() { return SP; };
	bool getComprado() { return comprado; };
	void setComprado() { comprado = true; };
	void cambiaSprite(int x);
	void setInventario(ShopState* recibe) { shop_ = recibe; };
};


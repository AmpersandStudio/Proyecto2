#pragma once
#include "GameState.h"

using namespace std;

class Item; //Incursión circular

class ShopState :
	public GameState
{
private:

	Texture* txF;
	Texture* txF2;
	Texture* Prueba;
	Texture* Prueba2;
	Texture* Prueba3;
	Game* game;
	int dinero;
	struct estado {
		bool empty;
		int identificador;
		int cantidad;
		int x;
		int y;
	};

	vector<Item*> mochila;
	estado** matriz;
	int ocupados;
	int elementos; int actFilas;
	int ultimaFilaY;
	int xM; int yM;

public:
	ShopState(Game* gamePtr);
	virtual ~ShopState();
	//virtual void render();
	//virtual bool handleEvent(SDL_Event& event);
	int devuelveDinero() { return dinero; };
	void cambiaDinero(int d);
	bool devMat(int& x, int& y, int ident, Item* elemento);
	void mouseEncima(int x, int y);
	void creaFila();
	void vuelveNormal();
	static void toMenu(Game* game);
};


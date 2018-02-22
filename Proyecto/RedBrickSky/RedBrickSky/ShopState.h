#pragma once
#include "GameState.h"
#include "RenderFullComponent.h"
#include "MouseScrollComponent.h"
#include "MouseOverObjectComponent.h"
#include "StateMachine.h"
#include "MouseInputComponentButton.h"

using namespace std;

class Item; //Incursión circular

class ShopState :
	public GameState
{
private:

	//TEXTURAS NECESARIAS
	Texture* back;
	Texture* standPoint;
	Texture* front;
	Texture* bot;

	//COMPONENTES NECESARIOS
	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	InputComponent* MSC;
	InputComponent* MSOC;
	InputComponent* MIC;

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
	int devuelveDinero() { return dinero; };
	void cambiaDinero(int d);
	bool devMat(int& x, int& y, int ident, Item* elemento);
	void creaFila();
	static void toMenu(Game* game);

};


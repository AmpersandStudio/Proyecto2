#pragma once
#include "GameState.h"
#include "RenderFullComponent.h"
#include "MouseScrollComponent.h"
#include "MouseOverObjectComponent.h"
#include "StateMachine.h"
#include "MouseInputComponentButton.h"
#include <vector>

#include "GameManager.h"

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
	Texture* food;

	//COMPONENTES NECESARIOS
	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	InputComponent* MSC;
	InputComponent* MSOC;
	InputComponent* MIC;

	Game* game;
	int money;

	vector<estado> invent;
	estado** matriz;
	int ocupados;
	int numSP; int actFilas;
	int ultimaFilaY;


public:
	ShopState(Game* gamePtr);
	virtual ~ShopState();
	int devuelveDinero() { return money; };
	void cambiaDinero(int d);
	bool devMat(int& x, int& y, int ident, Item* elemento);
	void creaFila();
	static void toMenu(Game* game);

};


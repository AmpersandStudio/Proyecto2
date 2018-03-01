#pragma once
#include "GameState.h"
#include "RenderFullComponent.h"
#include "MouseScrollShopComponent.h"
#include "MouseOverObjectComponent.h"
#include "StateMachine.h"
#include "MouseInputComponentButton.h"
#include "DragNDropShopComponent.h"
#include "MouseInfoClickComponent.h"
#include "GameComponent.h"
#include <vector>

#include "GameManager.h"

using namespace std;

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
	Texture* food2;
	Texture* food3;

	//COMPONENTES NECESARIOS
	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	InputComponent* MSC;
	InputComponent* MSOC;
	InputComponent* MIC;
	InputComponent* DND;
	InputComponent* DND2;
	InputComponent* Info;

	Game* game;
	int money;

	vector<estado> invent;
	vector<estado> shopObjects;
	vector<estado> SP;
	vector<GameComponent*> GCshopV;
	vector<GameComponent*> GCInventV;
	estado** matriz;
	int ocupados;
	int numSP; int actFilas;
	int ultimaFilaY;


public:
	ShopState(Game* gamePtr);
	virtual ~ShopState();
	int getMoney() { return money; };
	void setMoney(int d);
	void creaFila();
	static void toMenu(Game* game);
	//estado** devMat() { return matriz; };
	vector<estado> getInvent() { return invent; };
	void setInvent(estado s) { invent.push_back(s); };
	vector<estado> getSP() { return SP; };
	void setSP(vector<estado> s);
	void stageBack(GameComponent* s) { stage.push_back(s); };
};


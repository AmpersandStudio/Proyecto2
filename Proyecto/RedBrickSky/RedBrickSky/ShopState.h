#pragma once
#include "GameState.h"
#include "RenderFullComponent.h"
#include "RenderSingleFrameComponent.h"
#include "MouseScrollShopComponent.h"
#include "StateMachine.h"
#include "MouseInputComponentButton.h"
#include "DragNDropShopComponent.h"
#include "MouseInfoClickComponent.h"
#include "GameComponent.h"
#include <vector>
#include "ShopItems.h"

#include "GameManager.h"

using namespace std;

class ShopState :
	public GameState
{
private:
	//COMPONENTES NECESARIOS
	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	RenderComponent* rcSF;
	InputComponent* MSC;
	InputComponent* MSOC;
	InputComponent* MIC;
	InputComponent* DND;
	InputComponent* DND2;

	ShopItems* items;
	int money;

	vector<estado> invent;
	vector<estado> shopObjects;
	vector<estado> SP;
	vector<GameComponent*> GCshopV;
	vector<GameComponent*> GCInventV;

	//Vectores para los distintos tipos de objetos
	vector<estado> Weapons; //Vector para las armas
	vector<estado> Potions; //Vector para las pociones
	vector<estado> Objects; //Vector para los objetos

	int ocupados;
	int numSP; int actFilas;
	int ultimaFilaY;
	int auxOID;

	int Fils = 4;
	int Cols = 3;
	int Scols_ = 12;

	GameComponent* selector_;
	vector<GameObject*> StandPointsO;


public:
	ShopState();
	virtual ~ShopState();

	virtual bool handleEvent(const SDL_Event& event);

	int getMoney() { return money; };
	void setMoney(int d);
	static void toMenu();
	//estado** devMat() { return matriz; };
	vector<estado> getInvent() { return invent; };
	void setInvent(estado s) { invent.push_back(s); };
	vector<estado> getSP() { return SP; };
	void setSP(vector<estado> s);
	void stageBack(GameComponent* s) { stage.push_back(s); };
	void separateElements();
	void mainMenuBotton();
	void createShopItems();
	void createBagItems();
	void destroySP();
	void createSP();
};


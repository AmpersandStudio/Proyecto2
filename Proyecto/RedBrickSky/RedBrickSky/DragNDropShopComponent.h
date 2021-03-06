#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "GameComponent.h"
#include <iostream>

#include "checkML.h"

class ShopState;
class DragNDropShopComponent :
	public InputComponent
{
private:


	bool isMouseSelection;
	ShopState* shop;
	GameComponent* thisComponent;
	int price;
	bool comprado;
	int identifier;
	int tipo;
	string name;
	vector<estado> StandPoints;
	int filFrame; int colFrame;

public:
	DragNDropShopComponent(ShopState* s, int money, bool buy, int iden,GameComponent* component, int type,string n, int fil, int col);
	~DragNDropShopComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
	bool devMat(int x, int y, GameObject* o);
};


#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "GameComponent.h"

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
	vector<estado> StandPoints;

public:
	DragNDropShopComponent(ShopState* s, int money, bool buy, int iden,GameComponent* component);
	~DragNDropShopComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
	bool devMat(int x, int y, GameObject* o);
};


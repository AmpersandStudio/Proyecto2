#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "BackPack.h"
#include "ShopItems.h"
#include "checkML.h"

class KeyBoardShopComponent :
	public InputComponent
{
private:
	int X_;
	int Y_;
	int col_;
	int fil_;

	bool selection_ = false;
	int savedInvent = 0;

	int distance;

	int i = 0, j = 0;

	vector<GameObject* > SP;
	ShopState* shop;

	vector<estado> shopObjects;
public:
	KeyBoardShopComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b = nullptr, ShopState* s = nullptr);
	~KeyBoardShopComponent();
	bool handleEvent(GameObject* o, const SDL_Event& event);
};

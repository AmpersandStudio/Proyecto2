#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "BackPack.h"
#include "checkML.h"

class KeyBoardBackPackComponent :
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

	int knowWhereWeAre_;

	BackPack* bag;
	ShopState* shop;

	int i = 0, j = 0;

	vector<GameObject* > SP;

	vector<estado> Inventary;

	bool isLeft = false;
public:
	KeyBoardBackPackComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b = nullptr, ShopState* s = nullptr);
	~KeyBoardBackPackComponent();
	bool handleEvent(GameObject* o, const SDL_Event& event);
};


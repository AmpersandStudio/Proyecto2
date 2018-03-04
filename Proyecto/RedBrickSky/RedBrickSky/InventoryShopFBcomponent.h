#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "BackPack.h"

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

	BackPack* back;
	ShopState* shop;

	int i = 0, j = 0;

	vector<GameObject* > SP;

	vector<estado> invent;
public:
	KeyBoardBackPackComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b = nullptr, ShopState* s = nullptr);
	~KeyBoardBackPackComponent();
	bool handleEvent(GameObject* o, const SDL_Event& event);
};


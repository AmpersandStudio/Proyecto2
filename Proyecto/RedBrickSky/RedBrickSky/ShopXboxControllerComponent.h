#pragma once
#include "InputComponent.h"
#include "ShopState.h"
#include "XboxController.h"

class ShopXboxControllerComponent :
	public InputComponent
{
private:


	//////////////////////////////////////////

	int X_;
	int Y_;
	int col_;
	int fil_;

	bool selection_ = false;
	int savedInvent = 0;

	int distance;

	ShopItems* items;

	int i = 0, j = 0;

	vector<GameObject* > SP;
	ShopState* shop;

	vector<estado> shopObjects;

	/////////////////////////////////////
	const int m_joystickDeadZone = XboxController::Instance()->getDeadZone();

public:
	ShopXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s);
	~ShopXboxControllerComponent();

	bool handleEvent(GameObject* o, const SDL_Event& event);

};


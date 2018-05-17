#pragma once
#include "InputComponent.h"
#include "BackPack.h"
#include "checkML.h"
class BagXboxControllerComponent :
	public InputComponent
{
private: 


	int X_;
	int Y_;
	int col_;
	int fil_;
	int knowWhereWeAre_;

	bool selection_ = false;
	int savedInvent = 0;

	int distance;

	BackPack* bag;
	ShopState* shop;
	bool isLeft;
	int i = 0, j = 0;

	vector<GameObject* > SP;

	vector<estado> Inventary;

	/////////////////////////////////////
	const int m_joystickDeadZone = 10000;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;

public:
	BagXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b = nullptr, ShopState* s = nullptr);
	~BagXboxControllerComponent();

	bool handleEvent(GameObject* o, const SDL_Event& event);

	void move();

};


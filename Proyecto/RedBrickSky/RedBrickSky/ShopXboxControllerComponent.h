#pragma once
#include "InputComponent.h"
#include "ShopState.h"

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
	const int m_joystickDeadZone = 10000;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;


public:
	ShopXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s);
	~ShopXboxControllerComponent();
	void initialiseJoysticks();
	void onJoystickAxisMove(SDL_Event event);
	void onJoystickButtonDown(SDL_Event event);
	void onJoystickButtonUp(SDL_Event event);
	bool handleEvent(GameObject* o, const SDL_Event& event);
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
	void clean();

	//getters
	bool getButtonState(int joy, int buttonNumber) const { return m_buttonStates[joy][buttonNumber]; }
	//Posiciones de los sticks

};


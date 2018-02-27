#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "GameComponent.h"
#include "BackPack.h"

class DragNDropComponent :
	public InputComponent
{
private:
	bool isMouseSelection;
	GameComponent* thisComponent;
	int price;
	bool comprado;
	int identifier;
	vector<estado> StandPoints;
public:
	DragNDropComponent(BackPack* b);
	~DragNDropComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
	bool devMat(int x, int y, GameObject* o);
};


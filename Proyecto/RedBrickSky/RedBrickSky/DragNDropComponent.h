#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include "GameComponent.h"
#include "BackPack.h"

#include "checkML.h"

class DragNDropComponent :
	public InputComponent
{
private:
	BackPack * bag;
	bool isMouseSelection;
	GameComponent* thisComponent;
	int identifier;
	vector<estado> StandPoints;
	vector<estado> Inventary;

public:
	DragNDropComponent(BackPack* b, int id);
	~DragNDropComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
	bool devMat(int x, int y, GameObject* o);
	void swapElements();
};


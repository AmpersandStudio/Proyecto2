#pragma once
#include "InputComponent.h"
#include "GameManager.h"
#include <vector>

#include "checkML.h"

class BackPack;
class InventBottomsComponent :
	public InputComponent
{
private:
	BackPack* back;
	vector<estado> tipo;
	bool goingBack;
public:
	InventBottomsComponent(BackPack* b, vector<estado> v , bool vuelta);
	~InventBottomsComponent();
	virtual bool handleEvent(GameObject* o, const SDL_Event& event);
};


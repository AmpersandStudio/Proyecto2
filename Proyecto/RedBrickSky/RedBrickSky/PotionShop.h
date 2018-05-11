#pragma once
#include "InputComponent.h"
class PotionShop :
	public InputComponent
{
public:
	PotionShop();
	virtual ~PotionShop();
	bool handleEvent(GameObject* o, const SDL_Event& event);
};


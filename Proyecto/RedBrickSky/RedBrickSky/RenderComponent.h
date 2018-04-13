#pragma once
#include "GameObject.h"

#include "checkML.h"

class RenderComponent
{
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render(GameObject* o) = 0;
};


#pragma once
#include "RenderComponent.h"
class RenderFullComponent :
	public RenderComponent
{
public:
	RenderFullComponent();
	~RenderFullComponent();
	virtual void render(GameObject* o);
};


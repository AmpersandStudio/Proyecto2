#pragma once
#include "RenderComponent.h"
class RenderFullComponent :
	public RenderComponent
{
public:
	RenderFullComponent();
	~RenderFullComponent(); // SUPERCAQUÍSIMA
	virtual void render(GameObject* o);
};


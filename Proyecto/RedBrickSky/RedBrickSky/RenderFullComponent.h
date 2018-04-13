#pragma once
#include "RenderComponent.h"

#include "checkML.h"
class RenderFullComponent :
	public RenderComponent
{
public:
	RenderFullComponent();
	~RenderFullComponent(); // SUPERCAQUÍSIMA
	virtual void render(GameObject* o);
};


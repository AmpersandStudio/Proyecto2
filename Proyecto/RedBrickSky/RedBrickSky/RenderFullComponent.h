#pragma once
#include "RenderComponent.h"
class RenderFullComponent :
	public RenderComponent
{
public:
	RenderFullComponent();
	~RenderFullComponent(); // SUPERCAQU�SIMA
	virtual void render(GameObject* o);
};


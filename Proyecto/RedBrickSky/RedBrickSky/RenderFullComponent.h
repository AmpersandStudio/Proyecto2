#pragma once
#include "RenderComponent.h"

#include "checkML.h"
class RenderFullComponent :
	public RenderComponent
{
public:
	RenderFullComponent();
	~RenderFullComponent(); // SUPERCAQU�SIMA
	virtual void render(GameObject* o);
};


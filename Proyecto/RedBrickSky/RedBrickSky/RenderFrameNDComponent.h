#pragma once
#include "RenderComponent.h"

#include "checkML.h"
class RenderFrameNDComponent :
	public RenderComponent
{
public:
	RenderFrameNDComponent();
	~RenderFrameNDComponent();

	virtual void render(GameObject* o);
};


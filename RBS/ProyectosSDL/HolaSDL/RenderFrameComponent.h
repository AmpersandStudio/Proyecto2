#pragma once
#include "RenderComponent.h"
class RenderFrameComponent :
	public RenderComponent
{
public:
	RenderFrameComponent();
	~RenderFrameComponent();
	virtual void render(GameObject* o);
};


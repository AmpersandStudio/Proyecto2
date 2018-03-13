#pragma once
#include "RenderComponent.h"
class RenderSingleFrameComponent :
	public RenderComponent
{
public:
	RenderSingleFrameComponent();
	virtual ~RenderSingleFrameComponent();
	virtual void render(GameObject* o);
};


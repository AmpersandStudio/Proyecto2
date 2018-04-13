#pragma once
#include "RenderComponent.h"

#include "checkML.h"
class RenderFrameComponent :
	public RenderComponent
{
public:
	RenderFrameComponent();
	~RenderFrameComponent();
	virtual void render(GameObject* o);
};


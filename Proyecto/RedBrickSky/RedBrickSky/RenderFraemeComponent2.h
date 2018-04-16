#pragma once
#include "RenderComponent.h"
class RenderFraemeComponent2 :
	public RenderComponent
{
public:
	RenderFraemeComponent2();
	virtual ~RenderFraemeComponent2();
	virtual void render(GameObject* o);
};


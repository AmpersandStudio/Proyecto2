#include "RenderFullComponent.h"



RenderFullComponent::RenderFullComponent()
{
}


RenderFullComponent::~RenderFullComponent()
{
}

void RenderFullComponent::render(GameObject* o) {

	o->getText()->renderComplete();
}
#include "RenderFullComponent.h"
#include "TextureManager.h"


RenderFullComponent::RenderFullComponent()
{
}


RenderFullComponent::~RenderFullComponent()
{
}

void RenderFullComponent::render(GameObject* o) {

	TheTextureManager::Instance()->draw(o->getTextureId(), TheGame::Instance()->getRenderer());
}
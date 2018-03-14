#include "RenderSingleFrameComponent.h"
#include "TextureManager.h"

RenderSingleFrameComponent::RenderSingleFrameComponent()
{
}


RenderSingleFrameComponent::~RenderSingleFrameComponent()
{
}

void RenderSingleFrameComponent::render(GameObject* o) {

	int DestCellW = o->getWidth();
	int DestCellH = o->getHeight();
	Vector2D pos = o->getPosition();


	TheTextureManager::Instance()->drawItem(o->getTextureId(), pos.getX() * DestCellW, pos.getY() * DestCellH,
		DestCellW, DestCellH, o->getRowFrame(), o->getColFrame(), TheTextureManager::Instance()->getRows(o->getTextureId()), TheTextureManager::Instance()->getCols(o->getTextureId()),
		TheGame::Instance()->getRenderer(), o->getAngle(), o->getAlpha());
}
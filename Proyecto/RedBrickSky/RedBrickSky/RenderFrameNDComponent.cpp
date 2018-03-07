#include "RenderFrameNDComponent.h"



RenderFrameNDComponent::RenderFrameNDComponent()
{
}


RenderFrameNDComponent::~RenderFrameNDComponent()
{
}

void RenderFrameNDComponent::render(GameObject * o)
{
	int DestCellW = o->getWidth();
	int DestCellH = o->getHeight();

	Vector2D pos = o->getPosition();
	int scale = 1;

	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = DestCellW / scale;
	destRect.h = DestCellH / scale;

	
	o->getText()->renderFrame(destRect, o->getRowFrame(), o->getColFrame());
}

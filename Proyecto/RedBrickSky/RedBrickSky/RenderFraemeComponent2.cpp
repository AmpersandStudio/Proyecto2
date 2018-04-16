#include "RenderFraemeComponent2.h"
#include "TextureManager.h"

RenderFraemeComponent2::RenderFraemeComponent2()
{
}

RenderFraemeComponent2::~RenderFraemeComponent2()
{
}

void RenderFraemeComponent2::render(GameObject* o) {
	//Determinamos destino (matriz)
	int DestCellW = o->getWidth();
	int DestCellH = o->getHeight();

	Vector2D pos = o->getPosition();
	int scale = 1;

	SDL_Rect destRect;
	destRect.x = pos.getX() * DestCellW;
	destRect.y = pos.getY() * DestCellH;
	destRect.w = DestCellW / scale;
	destRect.h = DestCellH / scale;

	////Renderizamos textura del gc
	//o->getText()->renderFrame(destRect, o->getRowFrame(), o->getColFrame());
	////o->getText()->renderComplete();

	TheTextureManager::Instance()->drawF(o->getTextureId(), pos.getX() * DestCellW, pos.getY() * DestCellH,
		DestCellW, DestCellH, TheGame::Instance()->getRenderer(), o->getAngle(), o->getAlpha(), SDL_FLIP_NONE, o->getRowFrame(), o->getColFrame());

}
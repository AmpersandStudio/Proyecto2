#include "DragNDropShopComponent.h"
#include "MouseScrollShopComponent.h"
#include "RenderSingleFrameComponent.h"
#include <vector>
#include "GameState.h"
#include "ShopState.h"
#include "TextureManager.h"
#include "StringToScreen.h"


DragNDropShopComponent::DragNDropShopComponent(ShopState* s, int money, bool buy, int iden, GameComponent* comp, int type, string n, int fil, int col)
{
	isMouseSelection = false;
	shop = s;
	price = money;
	comprado = buy;
	tipo = type;
	identifier = iden;
	thisComponent = comp;
	name = n;
	filFrame = fil;
	colFrame = col;
}


DragNDropShopComponent::~DragNDropShopComponent()
{
}

bool DragNDropShopComponent::handleEvent(GameObject* o, const SDL_Event& event) {

	
	bool handledEvent = false;
	Vector2D position = o->getPosition();
	int x = 0;
	int y = 0;

	Vector2D v;

	SDL_GetMouseState(&x, &y); //comprobamos estado del raton

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT ) { //si es evento de raton

		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight())) {
			if (comprado) {
				StringToScreen::Instance()->setMessage("¡Ya tienes ese objeto!");
				StringToScreen::Instance()->startMessagin();
			}
			else 
			isMouseSelection = true;
		}
	}

	else if (event.type == SDL_MOUSEMOTION  && isMouseSelection && !comprado) {

		v.set((x - 38) / (o->getWidth()), (y - 40) / (o->getHeight()));
		o->setPosition(v);
	}

	else  if (event.type == SDL_MOUSEBUTTONUP && isMouseSelection) {
		isMouseSelection = false;

		if (devMat(x, y, o)) {
			TheSoundManager::Instance()->playSound("compra", 0);
			
			comprado = true;
		}

		o->setPosition(o->getOriPos());
	}

	return handledEvent;
}

bool DragNDropShopComponent::devMat(int x, int y, GameObject* o) {
	bool aceptada = false;

	int auxX;
	int auxY;
	int auxW;
	int auxH;
	int auxMx;
	int auxMy;
	bool encontrado = false;
	Vector2D v;
	StandPoints = shop->getSP();
	unsigned int i = 0;
	
	while (i < StandPoints.size() && !encontrado) {
		//Busca si el objeto se ha dejado en alguno de los Stand Points
		{
			auxX = StandPoints[i].x * 45;
			auxY = StandPoints[i].y * 45;
			auxW = StandPoints[i].w;
			auxH = StandPoints[i].h;
			auxMx = StandPoints[i].mX;
			auxMy = StandPoints[i].mY;

	if (x > (auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
	encontrado = true;
		}

	else 
		i++;
	}	
}

	if (encontrado) {
	
		if (StandPoints[i].empty == true) {
			
			if (GameManager::Instance()->getMoney() >= price && !comprado) {

				GameManager::Instance()->setMoney(GameManager::Instance()->getMoney() - price);
				StringToScreen::Instance()->setMessage("¡Objeto comprado! ");
				StringToScreen::Instance()->startMessagin();
				StringToScreen::Instance()->changeInfinite(0, "Caramelos: " + std::to_string(GameManager::Instance()->getMoney()));

				if (StandPoints[i].empty == true) {
					StandPoints[i].ID = identifier;
					StandPoints[i].empty = false;
					double posX, posY;
					posX = auxX + auxW / 2;
					posY = auxY + auxH / 2;

					v.set(posX / 45 -0.5 , posY / 45 - 0.5);
					o->setPosition(v);

					estado n;
					n.price = price;
					n.comprado = true;
					n.ID = identifier;
					n.empty = false;
					n.objects = StandPoints[i].objects;
					n.x = StandPoints[i].x;
					n.y = StandPoints[i].y;
					n.mX = 0;
					n.mY = 0;
					n.w = StandPoints[i].w;
					n.h = StandPoints[i].h;
					n.tx = o->getTextureId();
					n.type = tipo;
					n.nombre = name;
					n.FilFrame = filFrame;
					n.colFrame = colFrame;

					shop->setInvent(n);
					GameManager::Instance()->setInventory(n);

					GameComponent* gc2 = new GameComponent();
					gc2->setTextureId(o->getTextureId()); gc2->setOriPos(o->getOriPos()); gc2->setPosition(v); gc2->setWidth(45); gc2->setHeight(45);
					gc2->addRenderComponent(new RenderSingleFrameComponent()); 
					gc2->setColFrame(n.colFrame); gc2->setRowFrame(n.FilFrame);

					shop->stageBack(gc2);

					//Buscamos el objeto del inventario que tenga la misma fila y columna de frame para marcarlo como comprado
					vector<estado> aux = shop->getShopItems();
					for (int p = 0; p < aux.size(); p++) {

						if (aux[p].colFrame == o->getColFrame() && aux[p].FilFrame == o->getRowFrame()) {
							aux[p].comprado = true;
							shop->setShopObjects(aux);
							GameManager::Instance()->changeShopItems(aux);
						}
					}

				}

				shop->setSP(StandPoints);
				aceptada = true;


			}

			else if (GameManager::Instance()->getMoney() < price) {
				StringToScreen::Instance()->setMessage("¡No tienes dinero para pagar eso!");
				StringToScreen::Instance()->startMessagin();
			}
		}
		else {
			StringToScreen::Instance()->setMessage("¡Ahí hay algo! ");
			StringToScreen::Instance()->startMessagin();
		}
	}

	else if (!encontrado)
	{

		StringToScreen::Instance()->setMessage("¡Lo has puesto fuera!!");
		StringToScreen::Instance()->startMessagin();

	}

	return aceptada;
}

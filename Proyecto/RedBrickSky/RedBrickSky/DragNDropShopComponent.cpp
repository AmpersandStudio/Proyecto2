#include "DragNDropShopComponent.h"
#include "MouseScrollComponent.h"
#include <vector>
#include "GameState.h"
#include "ShopState.h"


DragNDropShopComponent::DragNDropShopComponent(ShopState* s, int money, bool buy, int iden, GameComponent* comp)
{
	isMouseSelection = false;
	shop = s;
	price = money;
	comprado = buy;
	identifier = iden;
	thisComponent = comp;
}


DragNDropShopComponent::~DragNDropShopComponent()
{
}

bool DragNDropShopComponent::handleEvent(GameObject* o, const SDL_Event& event) {

	StandPoints = shop->getSP();
	bool handledEvent = false;
	Vector2D position = o->getPosition();
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { //si es evento de raton

		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight()))
			isMouseSelection = true;
	}

	else if (event.type == SDL_MOUSEMOTION  && isMouseSelection && !comprado) {

		Vector2D v;
		v.set((x - 38) / (o->getWidth()), (y - 40) / (o->getHeight()));
		o->setPosition(v);
	}

	else  if (event.type == SDL_MOUSEBUTTONUP && isMouseSelection) {
		isMouseSelection = false;


		//cout << "Precio: " << precio << endl;

		if (!comprado && devMat(x, y, o) && shop->getMoney() >= price) {
			//xO = x - w / 2; yO = y - h / 2;
			shop->setMoney(price);
			
			cout << "Objeto comprado, tu dinero ahora es: " << shop->getMoney() << endl;
			//Invent->vuelveNormal();
		}

		else
		{
			//Invent->vuelveNormal();
			if (shop->getMoney() < price)
				cout << "No tienes dinero para pagar eso!" << endl;
			else
				cout << "Ahi ya hay algo!!!" << endl;
			o->setPosition(o->getOriPos());
		}
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
	

	unsigned int i = 0;
	while (i < StandPoints.size() && !encontrado) {
		//Busca si el objeto se ha dejado en alguno de los Stand Points
		{
			auxX = StandPoints[i].x * 70;
			auxY = StandPoints[i].y * 70;
			auxW = StandPoints[i].w;
			auxH = StandPoints[i].h;
			auxMx = StandPoints[i].mX;
			auxMy = StandPoints[i].mY;


	if (x > (auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
	encontrado = true;
		x = auxX + auxW / 2;
		y = auxY + auxH / 2;
		Vector2D v;
		v.set(x / 70, y / 70);
		o->setPosition(v);
		
	//cout << x << "," << y << "," << auxX << "," << auxY << "," << auxW << "," << auxH << endl;
		}
	}
		i++;
}

	if (encontrado) {

		if (StandPoints[i].empty == true || StandPoints[i].ID == identifier) {
			comprado = true;

			if (StandPoints[i].empty == true) {
				StandPoints[i].ID = identifier;
				StandPoints[i].empty = false;
				StandPoints[i].x = x;
				StandPoints[i].y = y;
				//ocupados++;
			}

			else {

				StandPoints[i].objects++;
				cout << "Tienes " << StandPoints[i].objects << " elementos del tipo " << identifier << " en tu inventario ahora." << endl;
			}

			estado n;
			n.price = price;
			n.comprado = comprado;
			n.ID = identifier;
			n.empty = false;
			n.objects = StandPoints[i].objects;
			n.x = StandPoints[i].x;
			n.y = StandPoints[i].y;
			n.mX = StandPoints[i].mX;
			n.mY = StandPoints[i].mY;
			n.w = StandPoints[i].w;
			n.h = StandPoints[i].h;
		
			shop->setInvent(n);
			//cout <<  mochila.size() << endl;

			aceptada = true;

		/*	if (numSP - ocupados == 1){
			shop->creaFila();
			}*/
		}
	}

	if (aceptada)
		shop->setSP(StandPoints);

	return aceptada;
}

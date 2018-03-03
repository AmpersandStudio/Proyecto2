#include "DragNDropShopComponent.h"
#include "MouseScrollShopComponent.h"
#include <vector>
#include "GameState.h"
#include "ShopState.h"


DragNDropShopComponent::DragNDropShopComponent(ShopState* s, int money, bool buy, int iden, GameComponent* comp, int type, string n)
{
	isMouseSelection = false;
	shop = s;
	price = money;
	comprado = buy;
	tipo = type;
	identifier = iden;
	thisComponent = comp;
	name = n;
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

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !comprado) { //si es evento de raton

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

		bool hueco = devMat(x, y, o);

		if (!comprado && hueco) {

			if (shop->getMoney() >= price) {
				shop->setMoney(price);
				cout << "Objeto comprado, tu dinero ahora es: " << shop->getMoney() << endl;
			}

			else if (shop->getMoney() < price)
				cout << "No tienes dinero para pagar eso!" << endl;
		}

		else if (hueco)
			cout << "Hay ya hay algo!!!" << endl;
		else 
			cout << "Lo has puesto fuera!!!!" << endl;

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
			
			//cout  << auxY << "," << endl;

	if (x > (auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
	encontrado = true;
		x = auxX + auxW / 2;
		y = auxY + auxH / 2;
		
		v.set(x / 70, y / 70);
		o->setPosition(v);

		//cout << auxMx << "," << auxMy << "," << endl;
	
	//cout << x << "," << y << "," << auxX << "," << auxY << "," << auxW << "," << auxH << endl;
		}

	else 
		i++;
	}
		
}

	if (encontrado) {
		//cout << StandPoints[i].ID << "," << identifier << endl;
		if (StandPoints[i].empty == true || StandPoints[i].ID == identifier) {
			//comprado = true;
			
			if (StandPoints[i].empty == true) {

				StandPoints[i].ID = identifier;
				StandPoints[i].empty = false;
				//StandPoints[i].x = x;
				//StandPoints[i].y = y;
				//ocupados++;
			}

			else {

				StandPoints[i].objects++;
				cout << "Tienes " << StandPoints[i].objects + 1 << " elementos del tipo " << identifier << " en tu inventario ahora." << endl;
			}

			estado n;
			n.price = price;
			n.comprado = comprado;
			n.ID = identifier;
			n.empty = false;
			n.objects = StandPoints[i].objects;
			n.x = StandPoints[i].x;
			n.y = StandPoints[i].y;
			n.mX = -1;
			n.mY = -1;
			n.w = StandPoints[i].w;
			n.h = StandPoints[i].h;
			n.tx = o->getText();
			n.type = tipo;
			n.nombre = name;
		
			shop->setInvent(n);
			GameManager::Instance()->setInventory(n);

			GameComponent* gc2 = new GameComponent(o->getGame());
			gc2->setText(o->getText()); gc2->setOriPos(o->getOriPos()); gc2->setPosition(v); gc2->setWidth(70); gc2->setHeight(70);
			gc2->addRenderComponent(new RenderFrameComponent()); gc2->addInputComponent(new MouseScrollShopComponent(shop));

			shop->stageBack(gc2);

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

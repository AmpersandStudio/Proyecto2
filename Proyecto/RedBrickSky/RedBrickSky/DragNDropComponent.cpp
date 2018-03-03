#include "DragNDropComponent.h"

DragNDropComponent::DragNDropComponent(BackPack* b, int id)
{
	bag = b;
	isMouseSelection = false;
	StandPoints = b->getSP();
	Inventary = b->getInvent();
	identifier = id;

}


DragNDropComponent::~DragNDropComponent()
{
}

bool DragNDropComponent::handleEvent(GameObject* o, const SDL_Event& event) {

	//StandPoints = shop->getSP();
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

	else if (event.type == SDL_MOUSEMOTION  && isMouseSelection) {

		Vector2D v;
		v.set((x - 38) / (o->getWidth()), (y - 40) / (o->getHeight()));
		o->setPosition(v);
	}

	else  if (event.type == SDL_MOUSEBUTTONUP && isMouseSelection) {
		isMouseSelection = false;

		if (!devMat(x, y, o))
			o->setPosition(o->getOriPos());	
	}
	return handledEvent;
}

bool DragNDropComponent::devMat(int x, int y, GameObject* o) {
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
			}

			else
				i++;
		}
	}

	if (encontrado) {
	
		if (StandPoints[i].empty == true) {

			StandPoints[i].ID = identifier;
			StandPoints[i].empty = false;
			x = auxX + auxW / 2;
			y = auxY + auxH / 2;

			Inventary[identifier].x = x;
			Inventary[identifier].y = y;
			Inventary[identifier].mX = auxMx;
			Inventary[identifier].mY = auxMy;

			bag->setInvent(Inventary);
			v.set(x / 70, y / 70);
			o->setPosition(v);
			o->setOriPos(v);
			aceptada = true;
		}
	}

	return aceptada;
}
